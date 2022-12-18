#include "message.h"

using namespace std;

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
void Message::unknownCommand() {
    cout << "There is no such command!" << endl;
    sleep(3);
}
void Message::helpMessage() {
    cout << "There are four commands:" << endl;
    cout << "1. help - show game reference." << endl;
    cout << "2. dump <filename> - save current universe state in file." << endl;
    cout << "3. exit - end the game." << endl;
    cout << "4. tick <n> - count game state after n iteration." << endl;
    sleep(3);
}