#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;

class TODO
{
public:
    void login();
    void registration();
    void todo_page();
    void addTask();
    void viewTasks();
    void deleteTasks();
    void markCompleted();
    void filterTask();
    void updateTasks();
    void searchTask();
    void sortTaskByPriority();
    void updateTaskCompletion();
    void exitProgram();
};

struct Task
{
    string description;      // Task description
    int priority;            // Task priority (1 = High, 2 = Medium, 3 = Low)
    bool completed;          // Task completion status
    string dateTime;         // variable for storing date and time
    string deadlineDateTime; // deadline
};

Task tasks[100];
int taskCount = 0;

int main()
{
    int choice;
    TODO todo;

    cout << "\t\t\t_\n\n\n";
    cout << "\t\t\t                WELCOME TO THE LOGIN PAGE                      \n\n\n";
    cout << "\t\t\t____________________           MENU            _________________\n\n\n";
    cout << "\t| Press 1 to LOGIN              |\n";
    cout << "\t| Press 2 to REGISTER           |\n";
    cout << "\t| Press 3 to EXIT               |\n";
    cout << "\n\t\t\t Please enter your choice: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
        todo.login();
        break;
    case 2:
        todo.registration();
        break;
    case 3:
        cout << "\t\t\t  EXIT  \n\n";
        break;
    default:
        system("cls");
        cout << "\t\t Please select from the options above \n"
             << endl;
        main();
    }
    return 0;
}

void TODO::login()
{
    string userId, password, id, pass;
    int count = 0;

    system("cls");
    cout << "\t\t\t Please enter the username and password: \n";
    cout << "\t\t\t USERNAME: ";
    cin >> userId;

    // Validate user input for username
    if (userId.empty())
    {
        cout << "Username cannot be empty.\n";
        return;
    }

    cout << "\t\t\t PASSWORD: ";
    cin >> password;

    // Validate user input for password
    if (password.empty())
    {
        cout << "Password cannot be empty.\n";
        return;
    }
    if (password.length() < 6)
    {
        cout << "Password must be at least 6 characters long.\n";
        getch();
        main();
    }

    fstream input("record.txt", ios::in | ios::out);
    while (input >> id >> pass)
    {
        if (id == userId && pass == password)
        {
            count = 1;
            system("cls");
            break;
        }
    }
    input.close();

    if (count == 1)
    {
        todo_page(); // Assuming todo_page() takes care of showing the user s tasks.
    }
    else
    {
        cout << "\n LOGIN ERROR \n Please check your username and password\n";
        getch();
        system("cls");
        main();
    }
}

void TODO::registration()
{
    string ruserId, rpassword;
    string id, pass;

    system("cls");
    cout << "\t\t\t Enter the Username: ";
    cin >> ruserId;

    // Validate username
    if (ruserId.empty())
    {
        cout << "Username cannot be empty.\n";
        return;
    }
    if (ruserId.length() < 3)
    {
        cout << "Username must be at least 3 characters long.\n";
        return;
    }

    // Check if username already exists
    fstream input("record.txt", ios::in | ios::out);
    while (input >> id >> pass)
    {
        if (id == ruserId)
        {
            cout << "Username already exists. Please choose a different username.\n";
            input.close();
            main();
        }
    }
    input.close();

    cout << "\t\t\t Enter the Password: ";
    cin >> rpassword;

    // Validate password
    if (rpassword.empty())
    {
        cout << "Password cannot be empty.\n";
        return;
    }
    if (rpassword.length() < 6)
    {
        cout << "Password must be at least 6 characters long.\n";
        return;
    }

    // Store the new username and password in the file
    fstream output("record.txt", ios::app);
    output << ruserId << ' ' << rpassword << endl;

    system("cls");
    cout << "\n\t\t\t Registration is successful! \n";
    getch();
    system("cls");
    main();
}

string getCurrentDateTime()
{
    time_t now = time(0);
    char dt[20];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(dt);
}

void TODO::addTask()
{
    fstream fin("task.txt", ios::in | ios::out);
    int maxSNo = 0;
    string line;

    while (getline(fin, line))
    {
        size_t pos = line.find('|');
        if (pos != string::npos)
        {
            int sno = stoi(line.substr(0, pos));
            maxSNo = max(maxSNo, sno);
        }
    }
    fin.close();

    int sno = maxSNo + 1;

    Task newTask;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask.description);

    cout << "Enter task priority (1 = High, 2 = Medium, 3 = Low): ";
    cin >> newTask.priority;

    // New deadline input
    cout << "Enter task deadline (YYYY-MM-DD HH:MM:SS format): ";
    cin.ignore();
    getline(cin, newTask.deadlineDateTime);

    newTask.completed = false;
    newTask.dateTime = getCurrentDateTime();

    fstream fout("task.txt", ios::app);
    if (!fout.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }
    fout << sno << " | " << newTask.description
         << " | Priority: " << newTask.priority
         << " | Status: Pending"
         << " | DateTime: " << newTask.dateTime
         << " | Deadline: " << newTask.deadlineDateTime << endl;
    fout.close();

    cout << "Task added successfully!\n";
    getch();
}

void TODO::viewTasks()
{
    fstream fin("task.txt", ios::in | ios::out);
    if (!fin.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }
    string line;

    cout << "--------------------------------------------------------------------------------------------------------------\n";
    cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time  | Deadline\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";


    bool hasTasks = false;
    while (getline(fin, line))
    {
        if (!line.empty())
        {
            hasTasks = true;
            cout << line << endl;
        }
    }
    fin.close();

    if (!hasTasks)
    {
        cout << "\tNo tasks available!" << endl;
    }
    getch();
}

void TODO::deleteTasks()
{
    fstream fin("task.txt", ios::in);
    fstream tempFile("temp.txt",ios::out);

    if (!fin.is_open() || !tempFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    int totalLines = 0, userSno;

    // Count total lines
    while (getline(fin, line))
    {
        if (!line.empty())
        {
            totalLines++;
        }
    }

    fin.close();

    if (totalLines == 0)
    {
        cout << "\nNo tasks available to delete!\n";
        tempFile.close();
        remove("temp.txt");
        getch();
        return;
    }

    // Reopen the file to display tasks
    fin.open("task.txt");

    // Display tasks
    cout << "\nYOUR TASKS:\n";
    int displayLineNum = 1;
    while (getline(fin, line))
    {
        if (!line.empty())
        {
            // Find the first '.' or ' ' to remove leading number
            size_t pos = line.find_first_of(". ");
            if (pos != string::npos)
            {
                line = line.substr(pos + 1);
            }
            cout << displayLineNum << ". " << line << endl;
            displayLineNum++;
        }
    }

    fin.close();

    cout << "\nEnter the SNo of the task to delete: ";
    cin >> userSno;

    if (userSno < 1 || userSno > totalLines)
    {
        cout << "Invalid SNo entered. Please try again.\n";
        tempFile.close();
        remove("temp.txt");
        getch();
        return;
    }

    // Reopen the file to copy tasks, skipping the one to be deleted
    fin.open("task.txt");
    int currentLine = 1;
    while (getline(fin, line))
    {
        if (!line.empty())
        {
            if (currentLine != userSno)
            {
                tempFile << line << endl;
            }
            currentLine++;
        }
    }

    fin.close();
    tempFile.close();

    remove("task.txt");
    rename("temp.txt", "task.txt");

    cout << "\nTask deleted successfully!\n";
    getch();
}

void TODO::markCompleted()
{
    fstream fin("task.txt", ios::in );
    fstream tempFile("temp.txt",ios::out);

    if (!fin.is_open() || !tempFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    int totalLines = 0;
    cout << "\nYOUR TASKS:\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time  | Deadline\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";


    // Temporary storage for tasks
    string *tasks = new string[100]; // Assuming max 100 tasks

    while (getline(fin, line))
    {
        if (!line.empty())
        {
            tasks[totalLines] = line;
            cout << line << endl;
            totalLines++;
        }
    }
    fin.close();

    if (totalLines == 0)
    {
        cout << "\nNo tasks available to mark as completed!\n";
        tempFile.close();
        remove("temp.txt");
        delete[] tasks;
        getch();
        return;
    }

    int sno;
    cout << "\nEnter the SNo of the task to mark as completed: ";
    cin >> sno;

    if (sno < 1 || sno > totalLines)
    {
        cout << "Invalid SNo entered. Please try again.\n";
        delete[] tasks;
        tempFile.close();
        remove("temp.txt");
        getch();
        return;
    }

    string selectedTask = tasks[sno - 1];
    size_t statusPos = selectedTask.find("Status: Pending");
    size_t deadlinePos = selectedTask.find("Deadline: ");

    if (statusPos != string::npos)
    {
        string currentDateTime = getCurrentDateTime();
        string deadlineDateTime = selectedTask.substr(deadlinePos + 10, 19);

        // Compare current time with deadline
        if (currentDateTime > deadlineDateTime)
        {
            cout << "\n WARNING: You are completing this task AFTER the deadline! \n";
            cout << "Task was due on: " << deadlineDateTime << "\n";
            cout << "You are completing it on: " << currentDateTime << "\n";
        }
        else
        {
            cout << "\n Task completed BEFORE deadline! Great job! \n";
        }

        // Update task status
        selectedTask.replace(statusPos, 15, "Status: Completed");

        // Add completion date
        size_t datePos = selectedTask.find("Deadline: ") + 19;
        selectedTask += " | Completed On: " + currentDateTime;
    }
    else
    {
        cout << "\nThe task is already marked as completed.\n";
    }

    // Write to temp file
    for (int i = 0; i < totalLines; i++)
    {
        if (i == sno - 1)
            tempFile << selectedTask << endl;
        else
            tempFile << tasks[i] << endl;
    }

    fin.close();
    tempFile.close();

    remove("task.txt");
    rename("temp.txt", "task.txt");

    delete[] tasks;
    getch();
}

void TODO::filterTask()
{
    int choice;
    do
    {
        system("cls");
        cout << "\nTASK VIEW MENU\n";
        cout << "1. View Pending Tasks\n";
        cout << "2. View Completed Tasks\n";
        cout << "3. Return to Previous Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            fstream fin("task.txt", ios::in);
            if (!fin.is_open())
            {
                cout << "Error opening the file!" << endl;
                return;
            }

            string line;
            bool hasPendingTasks = false;

            cout << "--------------------------------------------------------------------------------------------------------------\n";
            cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time  | Deadline\n";
            cout << "--------------------------------------------------------------------------------------------------------------\n";


            while (getline(fin, line))
            {
                if (line.find("Status: Pending") != string::npos)
                {
                    hasPendingTasks = true;
                    cout << line << endl;
                }
            }
            fin.close();

            if (!hasPendingTasks)
            {
                cout << "\nNo pending tasks found!\n";
            }
            getch();
            break;
        }

        case 2:
        {
            fstream fin("task.txt", ios::in);
            if (!fin.is_open())
            {
                cout << "Error opening the file!" << endl;
                return;
            }

            string line;
            bool hasCompletedTasks = false;

            cout << "\nCOMPLETED TASKS:\n";
            cout << "-----------------------------------------------------------------------------------------------------\n";
    cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time  | Deadline\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";


            while (getline(fin, line))
            {
                if (line.find("Status: Completed") != string::npos)
                {
                    hasCompletedTasks = true;
                    cout << line << endl;
                }
            }
            fin.close();

            if (!hasCompletedTasks)
            {
                cout << "\nNo completed tasks found!\n";
            }
            getch();
            break;
        }

        case 3:
            return;

        default:
            cout << "Invalid choice. Please try again.\n";
            getch();
        }
    } while (choice != 3);
}

void TODO::updateTasks()
{
    fstream fin("task.txt", ios::in );
    fstream tempFile("temp.txt", ios::out);

    if (!fin.is_open() || !tempFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    int totalLines = 0;
    // Temporary storage for tasks
    string *tasks = new string[100]; // Assuming max 100 tasks

    cout << "\nYOUR TASKS:\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time  | Deadline\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";


    while (getline(fin, line))
    {
        if (!line.empty())
        {
            tasks[totalLines] = line;
            cout << line << endl;
            totalLines++;
        }
    }
    fin.close();

    if (totalLines == 0)
    {
        cout << "\nNo tasks available to update!\n";
        tempFile.close();
        remove("temp.txt");
        delete[] tasks;
        getch();
        return;
    }

    int sno;
    cout << "\nEnter the SNo of the task you want to update: ";
    cin >> sno;

    if (sno < 1 || sno > totalLines)
    {
        cout << "Invalid SNo entered. Please try again.\n";
        tempFile.close();
        remove("temp.txt");
        delete[] tasks;
        getch();
        return;
    }

    string selectedTask = tasks[sno - 1];

    cout << "\nCurrent Task: " << selectedTask << endl;

    cout << "\nWhat would you like to update?\n";
    cout << "1. Description\n";
    cout << "2. Priority\n";
    cout << "3. Status\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "Enter new description: ";
        cin.ignore();
        string newDescription;
        getline(cin, newDescription);
        size_t descPos = selectedTask.find('|');
        if (descPos != string::npos)
        {
            selectedTask = to_string(sno) + " | " + newDescription + selectedTask.substr(descPos);
        }
        break;
    }
    case 2:
    {
        cout << "Enter new priority (1 = High, 2 = Medium, 3 = Low): ";
        int newPriority;
        cin >> newPriority;
        size_t priorityPos = selectedTask.find("Priority: ");
        if (priorityPos != string::npos)
        {
            selectedTask[priorityPos + 10] = '0' + newPriority;
        }
        break;
    }
    case 3:
    {
        cout << "Enter new status (1 = Pending, 2 = Completed): ";
        int statusChoice;
        cin >> statusChoice;
        string newStatus = (statusChoice == 2) ? "Completed" : "Pending";
        size_t statusPos = selectedTask.find("Status: ");
        if (statusPos != string::npos)
        {
            selectedTask.replace(statusPos + 8, newStatus.length(), newStatus);
        }
        break;
    }
    default:
        cout << "Invalid choice!\n";
        delete[] tasks;
        tempFile.close();
        remove("temp.txt");
        return;
    }

    tasks[sno - 1] = selectedTask;

    // Write updated tasks to temp file
    for (int i = 0; i < totalLines; i++)
    {
        tempFile << tasks[i] << endl;
    }

    tempFile.close();
    remove("task.txt");
    rename("temp.txt", "task.txt");

    delete[] tasks;
    cout << "\nTask updated successfully!\n";
    getch();
}

void TODO::searchTask()
{
    fstream fin("task.txt", ios::in);
    if (!fin.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    string keyword;
    cout << "Enter the keyword to search for in tasks: ";
    cin.ignore();
    getline(cin, keyword);

    string line;
    bool taskFound = false;

    cout << "\nSEARCH RESULTS:\n";
   cout << "--------------------------------------------------------------------------------------------------------------\n";
    cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time  | Deadline\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";


    while (getline(fin, line))
    {
        if (line.find(keyword) != string::npos)
        {
            taskFound = true;
            cout << line << endl;
        }
    }
    fin.close();

    if (!taskFound)
    {
        cout << "\nNo tasks found containing the keyword \"" << keyword << "\".\n";
    }

    getch();
}

void TODO::sortTaskByPriority()
{
    fstream file("task.txt", ios::in | ios::out);
    if (!file.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    // Read all lines
    string lines[100];
    int count = 0;
    string line;
    while (getline(file, line) && count < 100)
    {
        lines[count++] = line;
    }

    // Simple bubble sort by priority
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            int priorityA = lines[j].find("Priority: ") != string::npos ? lines[j][lines[j].find("Priority: ") + 10] - '0' : 3;
            int priorityB = lines[j + 1].find("Priority: ") != string::npos ? lines[j + 1][lines[j + 1].find("Priority: ") + 10] - '0' : 3;

            if (priorityA > priorityB)
            {
                swap(lines[j], lines[j + 1]);
            }
        }
    }

    // Rewrite the file
    file.close();
    fstream outFile("task.txt", ios::out);
    for (int i = 0; i < count; i++)
    {
        outFile << lines[i] << endl;
    }
    outFile.close();

    cout << "\nTasks sorted by priority successfully!\n";
    getch();
}

void TODO::updateTaskCompletion()
{
    string taskLines[100]; // Fixed-size array
    int taskCount = 0;     // To track the number of tasks read

    fstream fin("task.txt", ios::in);
    if (!fin.is_open())
    {
        cout << "Error opening the file!" << endl;
        return;
    }

    string line;
    cout << "\nYOUR TASKS:\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "SNo  | Description         | Priority | Status     | Date & Time           |Completed Date & Time   | Deadline\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";


    bool hasTasks = false;
    while (getline(fin, line) && taskCount < 100)
    {
        if (!line.empty())
        {
            hasTasks = true;
            taskLines[taskCount++] = line; // Store line in the array
            cout << line << endl;
        }
    }
    fin.close();

    if (!hasTasks)
    {
        cout << "\nNo tasks available to update!\n";
        getch();
        return;
    }

    int sno;
    cout << "\nEnter the SNo of the task to update completion percentage: ";
    cin >> sno;

    if (sno < 1 || sno > taskCount)
    { // Check against taskCount
        cout << "Invalid SNo entered. Please try again.\n";
        getch();
        return;
    }

    int completionPercentage;
    cout << "Enter the percentage of completion (0-100): ";
    cin >> completionPercentage;

    if (completionPercentage < 0 || completionPercentage > 100)
    {
        cout << "Invalid percentage. Please enter a value between 0 and 100.\n";
        getch();
        return;
    }

    size_t percentPos = taskLines[sno - 1].find("Completed (%)");
    if (percentPos != string::npos)
    {
        size_t endPos = taskLines[sno - 1].find(" ", percentPos + 13);
        taskLines[sno - 1].replace(percentPos + 13, endPos - (percentPos + 13), to_string(completionPercentage) + "%");
    }
    else
    {
        taskLines[sno - 1] += " | Completed (%): " + to_string(completionPercentage) + "%";
    }

    if (completionPercentage >= 100)
    {
        cout << "\nGreat job! You've completed your task. Keep up the good work!\n";
    }
    else
    {
        cout << "\nHURRY UP...Complete Your task\n";
    }

    fstream fout("task.txt", ios::out | ios::trunc);
    for (int i = 0; i < taskCount; ++i)
    { // Use taskCount to write back the tasks
        fout << taskLines[i] << endl;
    }
    fout.close();

    cout << "\nTask updated successfully!\n";
    getch();
}

void TODO::exitProgram()
{
    system("cls");
    cout << "\n\t\t\tThank you for using the TODO List!\n";
    cout << "\t\t\tExiting the program...\n";
    exit(0);
}

void TODO::todo_page()
{
    int option;

    do
    {
        system("cls");
        cout << "TO DO LIST_\n";
        cout << "1. Add New Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete All Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Filter Task\n";
        cout << "6. Update tasks\n";
        cout << "7. Search task by Name\n";
        cout << "8. Sort tasks by Priority\n";
        cout << "9. Update task Completion\n";
        cout << "10. Logout\n";
        cout << "11. EXIT Application\n";
        cout << "_\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            addTask();
            break;
        case 2:
            viewTasks();
            break;
        case 3:
            deleteTasks();
            break;
        case 4:
            markCompleted();
            break;
        case 5:
            filterTask();
            break;
        case 6:
            updateTasks();
            break;
        case 7:
            searchTask();
            break;
        case 8:
            sortTaskByPriority();
            break;
        case 9:
            updateTaskCompletion();
            break;
        case 10:
            cout << "\nLogging out...\n";
            system("cls");
            main();
        case 11:
            exitProgram();
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            getch();
            main();
        }
    }
    while(option != 11);
}

