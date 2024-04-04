#include<iostream>
#include<vector>
#include<string>
#include <limits>

constexpr auto CLEAR_SCREEN = "cls";

using namespace std;

struct Task
{
    string description;
    bool completed;
};

static void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

static string GetTaskDescription()
{
    string description;
    cout << "Enter Task Description: " << endl;
    getline(cin, description);
    return description;
}

static void clearScreen()
{
    system(CLEAR_SCREEN);
}

static void AddTask(vector<Task>& tasks)
{
    string description = GetTaskDescription();
    Task newTask;
    newTask.description = description;
    newTask.completed = false;
    char save;
    do {
        cout << "Are you sure you want to save? (Y/N): ";
        cin >> save;
        save = toupper(save);
    } while (save != 'Y' && save != 'N');

    if (save == 'Y') {
        tasks.push_back(newTask);
        cout << "Task Added Successfully." << endl;
    }
    else {
        cout << "Task does not Added." << endl;
    }
    clearInputBuffer();
}

static void viewTask(const vector<Task>& tasks)
{
    if (tasks.empty())
    {
        cout << "No Task Found." << endl;
        return;
    }

    cout << endl << "** Task List** " << endl;
    for (size_t i = 0;i < tasks.size();i++)
    {
        string status = tasks[i].completed ? "Completed" : "Pending";
        cout << i + 1 << "." << tasks[i].description << " ( " << status << " )" << endl;
    }
}

static void markTaskCompleted(vector<Task>& tasks)
{
    viewTask(tasks);
    if (tasks.empty())
    {
        return;
    }

    int taskNumber;
    cout << "Enter the Task Number you mark as completed." << endl;
    cin >> taskNumber;

    clearInputBuffer();
    if (taskNumber < 1 || taskNumber > tasks.size())
    {
        cout << "Invalid Task Number! Enter a number between 1 and " << tasks.size() << "." << endl;
        return;
    }

    char mark;
    do {
        cout << "Are you sure you Mark? (Y/N): ";
        cin >> mark;
        mark = toupper(mark);
    } while (mark != 'Y' && mark != 'N');

    if (mark == 'Y') {
        tasks[taskNumber - 1].completed = true;
        cout << "Task Marked Successfully." << endl;
    }
    else {
        cout << "Task does not Marked." << endl;
    }

}


static void UpdateTask(vector<Task>& tasks)
{
    viewTask(tasks);
    if (tasks.empty())
    {
        return;
    }

    int taskNumber;
    cout << "Enter the Task Number you want to update: ";
    cin >> taskNumber;

    clearInputBuffer();
    if (taskNumber < 1 || taskNumber > tasks.size())
    {
        cout << "Invalid Task Number! Enter a number between 1 and " << tasks.size() << "." << endl;
        return;
    }

    string newDescription = GetTaskDescription();

    char update;
    do {
        cout << "Are you sure you want to update it? (Y/N): ";
        cin >> update;
        update = toupper(update);
    } while (update != 'Y' && update != 'N');

    if (update == 'Y')
    {
        tasks[taskNumber - 1].description = newDescription;
        cout << "Task Updated Successfully." << endl;
    }
    else
    {
        cout << "Task not Updated." << endl;
    }

}


static void removeTask(vector<Task>& tasks)
{
    viewTask(tasks);
    if (tasks.empty())
    {
        return;
    }

    int taskNumber;
    cout << "Enter Task Number you want to delete!" << endl;
    cin >> taskNumber;

    clearInputBuffer();
    if (taskNumber < 1 || taskNumber > tasks.size())
    {
        cout << "Invalid Task Number! Enter a number between 1 and " << tasks.size() << "." << endl;
        return;
    }

    char remove;
    do {
        cout << "Are you sure you want to remove? (Y/N): ";
        cin >> remove;
        remove = toupper(remove);
    } while (remove != 'Y' && remove != 'N');

    if (remove == 'Y') {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task Removed Successfully." << endl;
    }
    else {
        cout << "Task does not Remove." << endl;
    }

}

int main()
{
    vector<Task> tasks;
    int choice;

    do
    {
        clearScreen();
        cout << "\n ** Task Menu ** " << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Task" << endl;
        cout << "3. Update Task" << endl;
        cout << "4. Mark Task as Completed" << endl;
        cout << "5. Remove Task" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your Choice Number." << endl;
        cin >> choice;

        clearInputBuffer();
        switch (choice)
        {
        case 1:
            AddTask(tasks);
            break;
        case 2:
            viewTask(tasks);
            break;
        case 3:
            UpdateTask(tasks);
            break;
        case 4:
            markTaskCompleted(tasks);
            break;
        case 5:
            removeTask(tasks);
            break;
        case 6:
            cout << "Thank You For Coming." << endl;
            break;
        default:
            cout << "Invalid Choice! " << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 6);
    return 0;
}