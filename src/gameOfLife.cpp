#include "gameOfLife.h"

using namespace std;

point::point(bool p_is_life, int xt, int yt)
{
    point_is_life = p_is_life;
    x = xt;
    y = yt;
}

void Message::startMessage() {
    cout << "Hello in my game of life!:)" << endl;
    cout << "There are two mods: offline and online" << endl;
    cout << "online mode: you just start programm and choose commands" << endl;
    cout << "offline mode: start it with -file <input file> -i <number of iterations> -o <output file>" << endl;
    cout << "There are such commands in online mode:" << endl;
    cout << "1. help - show game reference." << endl;
    cout << "2. dump <filename> -save current universe state." << endl;
    cout << "3. exit - end the game." << endl;
    cout << "4. tick <n> -count game state after n iteration." << endl;
    sleep(3);
    system("clear");
}
void Message::warningMessage() {
    cout << "Warning!" << endl;
    sleep(3);
}
void Message::unknowmcommand() {
    cout << "There is no such command!" << endl;
    sleep(3);
}
void Message::helpMessage() {
    cout << "There are such commands:" << endl;
    cout << "1. help - show game reference." << endl;
    cout << "2. dump<filename> -save current universe state." << endl;
    cout << "3. exit - end the game." << endl;
    cout << "4. tick <n> -count game state after n iteration." << endl;
    sleep(3);
}

int CommandState::readCommand()
{
    cin >> currentCommand;

    //Exit command
    if (currentCommand == "exit")
        return this->exit;

    //Dump game field command
    if (currentCommand == "dump")
        return this->dump;

    //Show field after n iteration
    if (currentCommand == "tick")
        return this->tick;

    //Show game reference
    if (currentCommand == "help")
        return this->help;

    return -1;
}

GameState::GameState(string file_name)
{
    ifstream fin;
    fin.exceptions(std::ifstream::badbit);
    fin.open(file_name.c_str());
    if (!fin.is_open())
        exit(1);

    regex universeNameRegex("[#N ]([A-Za-z]*)");
    regex roolsRegex("(#R )(B[0-9]+\/S[0-9]+)");
    regex sizeRegex("[#Size ]([0-9]+) ([0-9]+)");
    regex digits("[0-9]+");
    regex letters("[A-Za-z ]+");
    smatch s;

    char temp[256];

    //Read a name of universe
    fin.getline(temp, 256);
    if (std::regex_search(temp, universeNameRegex))
    {
        this->universeName = temp;
        this->universeName.erase(this->universeName.find("#N "), 3);
    }

    //Read rools for the game
    fin.getline(temp, 256);
    if (std::regex_search(temp, roolsRegex))
    {
        string str(temp);
        auto iter = sregex_iterator(str.begin(), str.end(), digits);
        s = *iter;
        this->gameRools = s.str();
        s = *(++iter);
        this->survivalRools = s.str();
    }

    //Read size of field
    fin.getline(temp, 256);
    if (std::regex_search(temp, sizeRegex))
    {
        std::string str(temp);
        auto iter = sregex_iterator(str.begin(), str.end(), digits);
        s = *iter;
        this->world_w = std::stol(s.str());
        s = *(++iter);
        this->world_h = std::stol(s.str());
    }

    //Read coordinates of cells
    int x, y;
    while (!fin.eof())
    {
        fin >> x >> y;
        this->cellsCoordinates.push_back(point(true, x, y));
    }

}

Field::Field(GameState& _game)
{
    game = &_game;
}

bool Field::should_be_born(int x)
{
    size_t found = game->gameRools.find(to_string(x));
    if (found != std::string::npos) return true;
    else return false;
}
bool Field::should_survive(int x)
{
    size_t found = game->survivalRools.find(to_string(x));
    if (found != std::string::npos) return true;
    else return false;
}

void Field::showRools()
{
    cout << "This universe have such Rules: " << endl;
    cout << "#N" << game->universeName << endl;
    cout << "#R " << "#B" << game->gameRools << "/" << "S" << game->survivalRools << endl;
    cout << "#S " << game->world_w << " " << game->world_h << endl;
    sleep(10);
}

void Field::saveField(string outputFile)
{
    std::ofstream fout(outputFile);
    fout << "#N " << game->universeName << endl;
    fout << "#R " << "#B" << game->gameRools << "/" << "S" << game->survivalRools << endl;
    fout << "#S " << game->world_w << " " << game->world_h << endl;

    for (size_t y = 0; y < game->world_h; y++)
    {
        for (size_t i = 0; i < game->world_w; i++)
        {
            if (world[i][y].point_is_life)
                fout << "* ";
            else
                fout << "  ";
        }
        fout << std::endl;
    }

}

void Field::nextWorld()
{
    vector<point> temp;

    int neighbours = 0, _x, _y, x_, y_; //x and y on top and bottom(left and right for x axis) :)
    for (int y = 0; y < game->world_h; y++)
    {
        for (int i = 0; i < game->world_w; i++)
        {
            neighbours = 0;
            bool isAlive = world[i][y].point_is_life;
            if (y == 0 && i==0) {
                _x = game->world_w - 1;
                x_ = i + 1;
                _y = game->world_h - 1;
                y_ = y + 1;
            }
            else if (y==0 && i==game->world_w-1){
                _x = i - 1;
                x_ = 0;
                _y = game->world_h - 1;
                y_ = y + 1;
            }
            else if (y == game->world_h-1 && i == 0) {
                _x = game->world_w - 1;
                x_ = i + 1;
                _y = y-1;
                y_ = 0;
            }
            else if (y == game->world_h - 1 && i == game->world_w - 1) {
                _x = i - 1;
                x_ = 0;
                _y = y - 1;
                y_ = 0;
            }
            else if (y == 0) {
                _x = i - 1;
                x_ = i + 1;
                _y = game->world_h - 1;
                y_ = y + 1;
            }
            else if (y == game->world_h - 1) {
                _x = i - 1;
                x_ = i + 1;
                _y = y - 1;
                y_ = 0;
            }
            else if (i == 0) {
                _x = game->world_w - 1;
                x_ = i + 1;
                _y = y - 1;
                y_ = y + 1;
            }
            else if (i == game->world_w - 1) {
                _x = i - 1;
                x_ = 0;
                _y = game->world_h - 1;
                y_ = y + 1;
            }
            else {
                _x = i - 1;
                x_ = i + 1;
                _y = y - 1;
                y_ = y + 1;
            }
            if (world[_x][_y].point_is_life) neighbours++;
            if (world[i][_y].point_is_life) neighbours++;
            if (world[x_][_y].point_is_life) neighbours++;

            if (world[_x][y].point_is_life) neighbours++;
            if (world[x_][y].point_is_life) neighbours++;

            if (world[_x][y_].point_is_life) neighbours++;
            if (world[i][y_].point_is_life) neighbours++;
            if (world[x_][y_].point_is_life) neighbours++;

            if (should_be_born(neighbours) && !isAlive)
                temp.push_back(point{ true, i, y });

            if (should_survive(neighbours) && isAlive)
                temp.push_back(point{ true, i, y });

            if (!should_survive(neighbours) && isAlive)
                temp.push_back(point{ false, i, y });

        }
    }
    for (auto& x : temp)
    {
        if (x.point_is_life)
            this->world[x.x][x.y].point_is_life = true;
        else
            this->world[x.x][x.y].point_is_life = false;
    }
    temp.resize(0);
}

void Field::initWorld()
{
    vector<point> temp;
    world.reserve(game->world_h);
    for (size_t y = 0; y < game->world_h; y++)
    {
        temp.resize(0);
        for (size_t i = 0; i < game->world_w; i++)
        {
            point z ={ 0, 0, 0 };
            temp.push_back(z);
        }
        world.push_back(temp);
    }

    for (auto &x : this->game->cellsCoordinates)
    {
        temp.reserve(game->world_w);
        world[x.x][x.y] = { true, x.x, x.y };
    }

}

void Field::printWorld()
{
    for (int y = 0; y < game->world_h; y++)
    {
        for (int x = 0; x < game->world_w; x++)
        {
            if (world[x][y].point_is_life)
            {
                cout << "* ";
            }
            else
                cout << "  ";
        }
        cout << endl;
    }
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
    field.showRools();
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
                cout << "Thank you for playing, hope to see you again :)" << endl;
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
                    system("clear");
                    field.printWorld();
                    sleep(10);
                    field.nextWorld();
                    iterations--;
                }

            }
            else
            {
                mym.warningMessage();
                mym.unknowmcommand();
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
