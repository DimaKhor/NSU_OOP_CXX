#include "gameOfLife.h"

using namespace std;

point::point(bool p_is_life, int xt, int yt)
{
    point_is_life = p_is_life;
    x = xt;
    y = yt;
}

void gameModeChoice(int& gameMode, int& iterations, string& inputFile, string& outputFile, int argc, char** argv)
{
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
                field.saveField(outputFile);
                cout << "file saved in: " << outputFile << "!";
            }
            else if (command == com.exit)
            {
                cout << "Thank you for playing, can't wait to see you again :)" << endl;
                exit(0);
            }
            else if (command == com.help)
            {
                mym.helpMessage();

            }
            else if (command == com.tick)
            {
                cin >> iterations;
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
    }
}
