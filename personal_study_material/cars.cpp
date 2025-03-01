#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <map>

using std::cout; using std::cin; using std::endl;
using std::sort;
using std::generate; using std::string; using std::vector;
using std::find_if; using std::max_element;
using std::unique; using std::map;

enum class Series { F1, NASCAR_CUP_SERIES, INDYCAR, WEC, IMSA, MotoGP, WRC, FormulaE, NASCAR_XFINITY_SERIES, NASCAR_TRUCK_SERIES };
string drivers[] = { 
    "Lewis Hamilton", "Sebastian Vettel", "Fernando Alonso", "Jimmy Johnson", "Dale Earnhardt", 
    "Scott Dixon", "Helio Castroneves", "Valentino Rossi", "Marc Marquez", "Jorge Lorenzo",
    "Kimi Raikkonen", "Daniel Ricciardo", "Max Verstappen", "Charles Leclerc", "Lando Norris",
    "Chase Elliott", "Kyle Busch", "Kevin Harvick", "Joey Logano", "Brad Keselowski",
    "Simon Pagenaud", "Josef Newgarden", "Alexander Rossi", "Will Power", "Ryan Hunter-Reay",
    "Danica Patrick", "Jamie McMurray", "Kurt Busch", "Martin Truex Jr.", "Denny Hamlin",
    "Ryan Blaney", "Erik Jones", "Clint Bowyer", "Aric Almirola", "Matt DiBenedetto",
    "Romain Grosjean", "Nico Hulkenberg", "Sergio Perez", "Esteban Ocon", "Lance Stroll",
    "George Russell", "Nicholas Latifi", "Pierre Gasly", "Daniil Kvyat", "Carlos Sainz",
    "Logan Sargeant", "Pato O'Ward", "Colton Herta", "Rinus VeeKay", "Oliver Askew",
    "Jack Harvey", "Scott McLaughlin", "Josef Newgarden", "Will Power", "Simon Pagenaud",
    "Alexander Rossi", "Ryan Hunter-Reay", "Sebastien Bourdais", "Graham Rahal", "Takuma Sato",
    "Aryton Senna", "Alain Prost", "Niki Lauda", "James Hunt", "Emerson Fittipaldi",
    "Gilles Villeneuve", "Jackie Stewart", "Juan Manuel Fangio", "Stirling Moss", "Jim Clark",
    "Mario Andretti", "A.J. Foyt", "Graham Hill", "Denny Hulme", "Jochen Rindt",
    "John Surtees", "Mike Hawthorn", "Phil Hill", "Alan Jones", "Keke Rosberg",
    "Nelson Piquet", "Nigel Mansell", "Mika Hakkinen", "Nico Rosberg", "Jenson Button", "Brad Pitt",
    "Lightning McQueen", "Doc Hudson", "Cruz Ramirez", "Jackson Storm", "Mater",
    "Jules Bianchi", "Robert Kubica", "Kamui Kobayashi", "Kazuki Nakajima", "Sebastien Buemi",
    "Oscar Piastri", "Robert Shwartzman", "Christian Lundgaard", "Guanyu Zhou", "Felipe Drugovich"
 };

 string tracks[] = {
    "Silverstone", "Monza", "Spa-Francorchamps", "Circuit de Monaco", "Suzuka",
    "Circuit of the Americas", "Indianapolis Motor Speedway", "Daytona International Speedway", "Le Mans",
    "Sebring International Raceway", "Road America", "Laguna Seca", "Watkins Glen", "Circuit Gilles Villeneuve",
    "Circuit de la Sarthe", "Nurburgring", "Brands Hatch", "Donington Park", "Imola",
    "Interlagos", "Bathurst", "Mount Panorama", "Circuit de Catalunya", "Hockenheimring",
    "Red Bull Ring", "Hungaroring", "Sochi Autodrom", "Shanghai International Circuit", "Bahrain International Circuit",
    "Yas Marina Circuit", "Circuit Paul Ricard", "Zandvoort", "Portimao", "Istanbul Park",
    "Sepang International Circuit", "Kyalami", "Circuit de Nevers Magny-Cours", "Circuit de Pau", "Circuit de Monaco"
 };

struct Racecar {
    int speed;
    Series series;
    string driver;

    bool operator<(const Racecar& other) const {
        return speed < other.speed;
    }
    bool operator>(const Racecar& other) const {
        return speed > other.speed;
    }
    bool operator==(const Racecar& other) const {
        return speed == other.speed;
    }
};

struct Track {
    string name;
    int length;
    Series series;
    Racecar winner;
};

string seriesToString(Series series) {
    switch (series) {
        case Series::F1: return "F1";
        case Series::INDYCAR: return "INDYCAR";
        case Series::WEC: return "WEC";
        case Series::IMSA: return "IMSA";
        case Series::MotoGP: return "MotoGP";
        case Series::WRC: return "WRC";
        case Series::FormulaE: return "FormulaE";
        case Series::NASCAR_XFINITY_SERIES: return "NASCAR_XFINITY_SERIES";
        case Series::NASCAR_TRUCK_SERIES: return "NASCAR_TRUCK_SERIES";
        case Series::NASCAR_CUP_SERIES: return "NASCAR_CUP_SERIES";
        default: return "Unknown";
    }
}

void Race(const Racecar* d1, const Racecar* d2, const string &driver1, const string &driver2) {
    if (d1 && d2) {
        cout << "Driver 1: " << d1->driver << ", Speed: " << d1->speed << ", Series: " << seriesToString(d1->series) << endl;
        cout << "Driver 2: " << d2->driver << ", Speed: " << d2->speed << ", Series: " << seriesToString(d2->series) << endl;
        cout << endl;

        if (*d1 > *d2) {
            cout << d1->driver << " wins!" << endl;
        }
        else if (*d1 < *d2) {
            cout << d2->driver << " wins!" << endl;
        }
        else {
            cout << "It's a tie!" << endl;
        }
    }

    else {
        if (!d1) {
            cout << driver1 << " not found!" << endl;
        }
        if (!d2) {
            cout << driver2 << " not found!" << endl;
        }
    }
    cout << endl;
}

void DriverWins(string driver, const vector<Racecar>& cars, const vector<Track>& raceResults) {
    auto it = std::find_if(cars.begin(), cars.end(), [&driver](const Racecar& car) {
        return car.driver == driver;
    });

    if (it != cars.end()) {
        cout << "Driver: " << it->driver << ", Speed: " << it->speed << ", Series: " << seriesToString(it->series) << endl;

        int wins = std::count_if(raceResults.begin(), raceResults.end(), [&driver](const Track& track) {
            return track.winner.driver == driver;
        });

        cout << "Wins: " << wins << endl;
    }
    else {
        cout << "Driver not found!" << endl;
    }
}

const Racecar* findDriver(const vector<Racecar>& cars, const string& driver) {
    auto it = std::find_if(cars.begin(), cars.end(), [&driver](const Racecar& car) {
        return car.driver == driver;
    });
    return it != cars.end() ? &(*it) : nullptr;
}

int main() {
    int SizeArray = sizeof(drivers) / sizeof(drivers[0]);
    //cout << SizeArray << endl;

    srand(time(0));
    vector<Racecar> cars;

    //generate random cars with random drivers
    cars.resize(rand() % 200 + 1);
    //cars.resize(10);
    generate(cars.begin(), cars.end(), [SizeArray]() {
        return Racecar{ rand() % 200 + 100, static_cast<Series>(rand() % 10), drivers[rand() % SizeArray] };
    });

    //remove duplicates by driver
    std::sort(cars.begin(), cars.end(), [](const Racecar& a, const Racecar& b) {
        return a.driver < b.driver;
    });
    cars.erase(unique(cars.begin(), cars.end(), [](const Racecar& a, const Racecar& b) {
        return a.driver == b.driver;
    }), cars.end());

    for (auto& car : cars) {
        cout << "Driver: " << car.driver << ", Speed: " << car.speed << ", Series: " << seriesToString(car.series) << endl;
    }
    cout << endl;

    cout << "Number of cars: " << cars.size() << endl;

    auto findFastestDriver = [](const vector<Racecar>& cars, Series series) {
        auto fastest = std::max_element(cars.begin(), cars.end(), [series](const Racecar& a, const Racecar& b) {
            return (a.series == series ? a.speed : -1) < (b.series == series ? b.speed : -1);
        });
        if (fastest != cars.end() && fastest->series == series) {
            cout << "Fastest " << seriesToString(series) << " driver: " << fastest->driver << endl;
        }
    };

    findFastestDriver(cars, Series::F1);
    findFastestDriver(cars, Series::INDYCAR);
    findFastestDriver(cars, Series::WEC);
    findFastestDriver(cars, Series::IMSA);
    findFastestDriver(cars, Series::MotoGP);
    findFastestDriver(cars, Series::WRC);
    findFastestDriver(cars, Series::FormulaE);
    findFastestDriver(cars, Series::NASCAR_CUP_SERIES);
    findFastestDriver(cars, Series::NASCAR_XFINITY_SERIES);
    findFastestDriver(cars, Series::NASCAR_TRUCK_SERIES);

    cout << endl;

    // have two drivers race
    cout << "Enter two drivers to race each other: " << endl;
    cout << "Driver 1: ";
    string driver1;
    getline(cin, driver1);
    cout << "Driver 2: ";
    string driver2;
    getline(cin, driver2);

    cout << endl;

    const Racecar* d1 = findDriver(cars, driver1);
    const Racecar* d2 = findDriver(cars, driver2);

    Race(d1, d2, driver1, driver2);


    ////debuging findDriver
    //cout << "Driver to find: ";
    //string driver1;
    //getline(cin, driver1);
    //for (auto& car : cars) {
    //    if (car.driver == driver1) {
    //        cout << "Driver: " << car.driver << ", Speed: " << car.speed << ", Series: " << seriesToString(car.series) << endl;
    //    }
    //}

    int SizeArrayTracks = sizeof(tracks) / sizeof(tracks[0]);
    vector<Track> raceResults;
    raceResults.resize(SizeArrayTracks);
    generate(raceResults.begin(), raceResults.end(), [&cars, SizeArrayTracks]() {
        Series series = static_cast<Series>(rand() % 10);
        vector<Racecar> seriesCars;
        std::copy_if(cars.begin(), cars.end(), std::back_inserter(seriesCars), [series](const Racecar& car) {
            return car.series == series;
        });
        const Racecar& winner = seriesCars.empty() ? Racecar{0, series, "No Winner"} : seriesCars[rand() % seriesCars.size()];
        return Track{ tracks[rand() % SizeArrayTracks], rand() % 1000 + 100, series, winner };
    });

    //sort by series
    std::sort(raceResults.begin(), raceResults.end(), [](const Track& a, const Track& b) {
        return a.series < b.series;
    });

    cout << " Number of Races this Season: " << raceResults.size() << endl;
    cout << "Race Results: " << endl;

    for (auto& track : raceResults) {
        cout << "Track: " << track.name << ", Length: " << track.length << ", Series: " << seriesToString(track.series) << ", Winner: " << track.winner.driver << endl;
    }
    cout << endl;

    // search for a driver & get their series, speed, & track wins
    cout << "Enter a driver to search for: ";
    string driver;
    getline(cin, driver);

    DriverWins(driver, cars, raceResults);


    return 0;
};