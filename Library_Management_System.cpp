#include<iostream>
#include<string>
#include<ctime>
#include<sstream>
#include<iomanip>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>

constexpr auto CLEAR_SCREEN = "cls";

using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PASSWORD = "2461HMtf.";
const char* DATABASE = "library";

const double FINE_RATE = 0.5;

static void clearScreen()
{
	system(CLEAR_SCREEN);
}




static void addBooks(MYSQL* conn)
{
	string title, author, isbn;

	cout << "Enter your Book Title: ";
	cin.ignore();
	cin>> title;

	string check = "SELECT COUNT(*) FROM addbook WHERE title = '" + title + "'";
	if (mysql_query(conn, check.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res) {
		MYSQL_ROW row = mysql_fetch_row(res);
		int count = atoi(row[0]);
		mysql_free_result(res);

		if (count > 0) {
			cout << "Book with the same title already exists. Please choose a different title." << endl;
			return;
		}
	}
	else {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	cin.ignore();
	cout << "Enter your Book Author: ";
	getline(cin,author);

	bool validISBN = false;
	while (!validISBN) {
		cout << "Enter your Book ISBN (exactly 13 characters): ";
		cin >> isbn;
		if (isbn.length() == 13) {
			validISBN = true;
		}
		else {
			cout << "ISBN should be exactly 13 characters long.\n";
		}
	}

	string query = "INSERT INTO addbook (title, author, ISBN, available) VALUES ('" + title + "', '" + author + "', '" + isbn + "', true)";
	if (mysql_query(conn, query.c_str()))
	{
		cout << mysql_error(conn)<< endl;
	}
	else
	{
		cout << "Data Inserted Successfully. " << endl;
	}
}


static void searchBooks(MYSQL* conn) {
	string keyword;
	cout << "Enter search keyword (title, author, or ISBN): ";
	cin.ignore();
	getline(cin, keyword);

	string query = "SELECT * FROM addbook WHERE title LIKE '%" + keyword + "%' OR author LIKE '%" + keyword + "%' OR ISBN LIKE '%" + keyword + "%'";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res) {
		cout << "Search Results:\n";
		while (MYSQL_ROW row = mysql_fetch_row(res)) {
			cout << endl;
			cout << "Title: " << row[1]<< endl << "Author: " << row[2] << endl << "ISBN: " << row[3] << endl <<endl<<endl;
		}
		mysql_free_result(res);
	}
	else {
		cout << "No results found.\n";
	}
}


static void showBooks(MYSQL* conn) {
	string query = "SELECT * FROM addbook";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res) {
		cout << "All Books:\n";
		while (MYSQL_ROW row = mysql_fetch_row(res)) {
			cout << "Title: " << row[1] << endl
				<< "Author: " << row[2] << endl
				<< "ISBN: " << row[3] << endl
				<< "Availability: " << row[4] << endl << endl;
		}
		mysql_free_result(res);
	}
	else {
		cout << "No books found.\n";
	}
}


static void checkoutBook(MYSQL* conn) {
	string book_title,book_author;
	cout << "Enter book Title to checkout: ";
	cin >> book_title;

	string query = "SELECT available FROM addbook WHERE title = '" + book_title + "'";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}
	MYSQL_RES* res = mysql_store_result(conn);
	if (res) {
		MYSQL_ROW row = mysql_fetch_row(res);
		bool available = atoi(row[0]);
		mysql_free_result(res);
		if (!available) {
			cout << "Book is not available for checkout.\n";
			return;
		}
	}
	else {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	query = "UPDATE addbook SET available = false WHERE title = '" + book_title + "'";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	query = "INSERT INTO transactions (book_title, checkout_date) VALUES ('"+ book_title +"', NOW())";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Book checked out successfully.\n";
}


static void returnBook(MYSQL* conn) {
	string transaction_book;
	cout << "Enter transaction Book to return book: ";
	cin >> transaction_book;

	string query = "UPDATE addbook SET available = true WHERE title = (SELECT book_title FROM transactions WHERE book_title = '"+ transaction_book +"')";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	query = "UPDATE transactions SET return_date = NOW() WHERE book_title = '" + transaction_book + "'";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	cout << "Book returned successfully.\n";
}




static double calculateFine(int daysOverdue)
{
	return daysOverdue * FINE_RATE;
}

static int getDaysDifference(const string& startDate, const string& endDate)
{
	tm start = {};
	istringstream(startDate) >> get_time(&start, "%Y-%m-%d");
	time_t start_time = mktime(&start);

	tm end = {};
	istringstream(endDate) >> get_time(&end, "%Y-%m-%d");
	time_t end_time = mktime(&end);

	double difference = difftime(end_time, start_time);

	return difference / (60 * 60 * 24);
}

static void calculateFineForBook(MYSQL* conn)
{
	string transaction_book;
	cout << "Enter transaction Book to calculate fine: ";
	cin >> transaction_book;

	string query = "SELECT return_date FROM transactions WHERE book_title = '" + transaction_book + "'";
	if (mysql_query(conn, query.c_str())) {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	if (res) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row[0] == nullptr) {
			cout << "Book hasn't been returned yet." << endl;
			return;
		}
		string returnDate = row[0];
		mysql_free_result(res);

		query = "SELECT checkout_date FROM transactions WHERE book_title = '" + transaction_book + "'";
		if (mysql_query(conn, query.c_str())) {
			cout << "Error: " << mysql_error(conn) << endl;
			return;
		}

		MYSQL_RES* res2 = mysql_store_result(conn);
		if (res2) {
			MYSQL_ROW row2 = mysql_fetch_row(res2);
			string checkoutDate = row2[0];
			mysql_free_result(res2);

			int daysOverdue = getDaysDifference(checkoutDate, returnDate);
			if (daysOverdue > 0) {
				double fine = calculateFine(daysOverdue);
				cout << "Fine for overdue: $" << fixed << setprecision(2) << fine << endl;
			}
			else {
				cout << "No fine. Book returned on time." << endl;
			}
		}
		else {
			cout << "Error: " << mysql_error(conn) << endl;
			return;
		}
	}
	else {
		cout << "Error: " << mysql_error(conn) << endl;
		return;
	}
}



int main()
{
	MYSQL* conn = nullptr;
	conn = mysql_init(conn);
	if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0))
	{
		cout << mysql_error(conn);
	}
	else
	{
		cout << "Connecton Successful. " << endl;
	}
	Sleep(2000);

	int choice;

	do
	{
		clearScreen();
		cout << " ***Library Management System*** " << endl;
		cout << "1. Add Books" << endl;
		cout << "2. Search Books" << endl;
		cout << "3. Show Books" << endl;
		cout << "4. Checkout Book" << endl;
		cout << "5. Return Book" << endl;
		cout << "6. Calculate Fine" << endl;
		cout << "7. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			addBooks(conn);
			break;
		case 2:
			searchBooks(conn);
			break;
		case 3:
			showBooks(conn);
			break;
		case 4:
			checkoutBook(conn);
			break;
		case 5:
			returnBook(conn);
			break;
		case 6:
			calculateFineForBook(conn);
			break;
		case 7:
			cout << "Thank you for Coming."<<endl;
			break;
		default:
			cout << "Invalid Choice.";
		}
		cout << "Press Enter to continue...";
		cin.ignore();
		cin.get();
		
	}
	while (choice != 7);
	mysql_close(conn);
	
}
