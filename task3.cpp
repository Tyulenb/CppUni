#include <iostream>
#include <string>
#include <list>
#include <queue>

using namespace std;

struct Passenger {
    string lastName;
    string destination;
    string date;
};

struct Ticket {
    string number;
    string destination;
    string date;
    int amount = 0;
};

void printTickets(list<Ticket> &tcks) {
    for (Ticket tck : tcks) {
        cout << tck.number << " " << tck.destination << " " << tck.date << " " << tck.amount << "\n";
    }
}

void printPassengers(queue<Passenger> &passengers) {
    int iters = passengers.size();
    while (iters > 0) {
        Passenger curPassenger = passengers.front();
        passengers.pop();
        cout << curPassenger.lastName << " " << curPassenger.destination << " " << curPassenger.date << "\n";
        passengers.push(curPassenger);
        iters--;
    }
}

int main(){
    setlocale(LC_ALL, "Russian");
    list<Ticket> tickets;
    cout << "Введите количество типов билетов: ";
    int am; cin >> am;
    for (int i = 0; i < am; i++) {
        Ticket tck;
        cout << "\nДля билета " << i + 1 << " введите номер рейса билета : ";
        cin >> tck.number;
        cout << "Для билета " << i + 1 << " введите пункт прибытия : ";
        cin >> tck.destination;
        cout << "Для билета " << i + 1 << " введите дату вылета : ";
        cin >> tck.date;
        cout << "Для билета " << i + 1 << " введите кол-во билетов : ";
        cin >> tck.amount;
        tickets.push_back(tck);
    }

    cout << "\nВведите количество пассажиров: ";
    cin >> am;
    queue<Passenger> passengers;
    for (int i = 0; i < am; i++) {
        Passenger ps;
        cout << "\nДля пассажира " << i + 1 << " введите фамилию: ";
        cin >> ps.lastName;
        cout << "Для пассажира " << i + 1 << " введите пункт прибытия: ";
        cin >> ps.destination;
        cout << "Для пассажира " << i + 1 << " введите дату вылета: ";
        cin >> ps.date;
        passengers.push(ps);
    }
    

    cout << "\nДоступные билеты\n";
    printTickets(tickets);

    cout << "\nПассажиры\n";
    printPassengers(passengers);
    cout << "\n";


    int iters = passengers.size();
    while (iters > 0) {
        string number = "";
        Passenger curPassenger = passengers.front();
        passengers.pop();
        for (list<Ticket>::iterator tck = tickets.begin(); tck != tickets.end(); ++tck) {
            if (tck->date == curPassenger.date) {
                if (tck->destination == curPassenger.destination) {
                    if (tck->amount > 0) {
                        tck->amount-=1;
                        number = tck->number;
                        break;
                    }
                }
            }
        }
        if (number=="") {
            passengers.push(curPassenger);
        }
        else {
            cout << curPassenger.lastName << " Успешно приобрел билет на рейс " << number << "\n";
        }
        iters--;
    }
    cout << "\nОставшиеся билеты\n";
    printTickets(tickets);
    cout << "\nОставшиеся пассажиры\n";
    printPassengers(passengers);

}

