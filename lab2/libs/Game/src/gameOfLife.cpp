#include "gameOfLife.h"

using namespace std;

void gameModeChoice(int& gameMode, int& iterations, string& inputFile, string& outputFile, int argc, char** argv)
{
    const int offline = 0;

    Message mym;
    mym.startMessage();

    if (argc > 1) {
        gameMode = offline;
        for (int i = 1; i < argc; i++)
        {
            if (argv[i] == string("-i"))
            {
                iterations = stoi(argv[i + 1]);
            }

            if (argv[i] == string("-o"))
            {
                string temp = argv[i + 1];
                outputFile = string(temp.begin(), temp.end());
            }
            if (argv[i] == string("-file"))
            {
                string temp = argv[i + 1];
                inputFile = string(temp.begin(), temp.end());
            }
        }
    }
}

void gameOfLife(Field field, int gameMode, int iterations, string outputFile)
{
    const int online = 1;

    field.initWorld();
    field.showRules();
    int command;
    if (gameMode == online) {
        CommandState com;

        Message mym;

        while (true) {
            command = com.readCommand();
            if (command == com.dump)
            {
                cin >> outputFile;
                field.saveField(outputFile);
                cout << "file saved in: " << outputFile << "!\n";
            }
            else if (command == com.exit)
            {
                cout << "Thank you for playing, can't wait to see you again :)" << endl;
                return;
            }
            else if (command == com.help)
            {
                mym.helpMessage();
            }
            else if (command == com.tick)
            {
                string except;
                cin >> except;

                try {
                    iterations = stoi(except);
                }
                catch(exception& exc) {
                    mym.warningMessage();
                    mym.unknownCommand();
                    continue;
                }

                while (iterations > 0)
                {
                    if (iterations == 1)
                    {
                        system("clear");
                        field.printWorld();
                    }
                    field.nextWorld();
                    iterations--;
                }

            }
            else
            {
                mym.warningMessage();
                mym.unknownCommand();
            }
        }
    }
    else {
        while (iterations > 0) {
            system("clear");
            field.printWorld();
            sleep(1);
            field.nextWorld();
            iterations--;
        }
        field.saveField(outputFile);

        cout << "file saved in: " << outputFile << "!";

        return;
    }
}
