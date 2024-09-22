// Copyright 2023
// Author: NNwachukwu
/* This is a program novel that allows the user to:
login with a username and password then,
allows the user to input any date and find out the zodiac sign,then,
input any zodiac sign and know the general characteristics of that zodiac sign,
and finally input any zodiac sign to know the description of the symbol-
for the sign. Which are four services in total.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::string;
using std::vector;

// Function prototypes
void loadZodiacSignsFromFile();
void loadUsersFromFile();
void saveUsersToFile();
void printMenu();
bool login(string username, string password);
string findZodiacSign(const string& birthDate);
string getCharacteristics(const string& zodiacSign);
string getZodiacSymbol(const string& zodiacSign);
int convertDateToValue(const string& date);

// Global variables
vector<string> users;
vector<string> zodiacSigns;

bool authenticated = false;  // Flag to track if a user is authenticated

int main() {
    loadZodiacSignsFromFile();
    loadUsersFromFile();
    saveUsersToFile();

    printMenu();
    return 0;
}
// Load zodiacs from file
void loadZodiacSignsFromFile() {
    ifstream zodiacFile("userzodiacs.txt");  // File for zodiac sign
    if (!zodiacFile) {
        cout << "Error opening userzodiacs.txt!" << endl;
        return;
    }

    string zodiac;
    while (getline(zodiacFile, zodiac)) {
        zodiacSigns.push_back(zodiac);
    }

    zodiacFile.close();
}

void loadUsersFromFile() {
    ifstream userFile("user_accounts.txt");  // User account files
    if (!userFile) {
        cout << "Error opening user_accounts.txt!" << endl;
        return;
    }

    string user;
    while (getline(userFile, user)) {
        users.push_back(user);
    }

    userFile.close();
}
// Save users to file user_accounts.txt
void saveUsersToFile() {
    ofstream userFileOut("user_accounts.txt");
    if (!userFileOut) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (const string& user : users) {
        size_t spacePos = user.find(' ');
        if (spacePos != string::npos) {
            string username = user.substr(0, spacePos);
            string password = user.substr(spacePos + 1);
            userFileOut << username << ' ' << password << '\n';
        }
    }

    userFileOut.close();
}
// Print menu
void printMenu() {
    int choice;
    string username, password;

    do {
cout <<"Welcome to Zees Astrologies Application. Find out your zodiac!"<< endl;
        if (!authenticated) {
            cout << "Please log in to continue." << endl;
            cout << "1. Login" << endl;
            cout << "2. Exit" << endl;
            cout << "Please make a selection: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "Enter your username: ";
                    cin >> username;
                    cout << "Enter your password: ";
                    cin >> password;
                    if (login(username, password)) {
                        cout << "Login successful!" << endl;
                        authenticated = true;
                    } else {
                cout << "Invalid login details. Please try again." << endl;
                    }
                    break;
                }
                case 2: {
cout << "Exiting... I hope we helped you find your zodiac! Goodbye!" << endl;
                    return;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        } else {
            cout << "Please enter make a selection:" << endl;
            cout << "1. Find your Zodiac Sign" << endl;
            cout << "2. Zodiac Characteristics" << endl;
            cout << "3. Zodiac Symbol Description" << endl;
            cout << "4. Log Out" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string birthDate;
                    cout << "Enter your birth date (MM-DD): ";
                    cin >> birthDate;
                    string zodiacSign = findZodiacSign(birthDate);
                    cout << "Your Zodiac Sign is: " << zodiacSign << endl;
                    break;
                }
                case 2: {
                    string zodiacSign;
                    cout << "Please enter your zodiac sign: ";
                    cin >> zodiacSign;
                    string characteristics = getCharacteristics(zodiacSign);
                    cout << characteristics << endl;
                    break;
                }
                case 3: {
                    string zodiacSign;
                    cout << "Please enter your zodiac sign: ";
                    cin >> zodiacSign;
                    string symbolDescription = getZodiacSymbol(zodiacSign);
    cout << "Zodiac Symbol Description: " << symbolDescription << endl;
                    break;
                }
                case 4: {
                    cout << "Logging out... Goodbye!" << endl;
                    authenticated = false;
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        }
    } while (true);
}
// login
bool login(string username, string password) {
    for (const string& user : users) {
        size_t spacePos = user.find(' ');
        if (spacePos != string::npos) {
            string storedUsername = user.substr(0, spacePos);
            string storedPassword = user.substr(spacePos + 1);
            if (storedUsername == username && storedPassword == password) {
                return true;
            }
        }
    }
    return false;
}


// Function to convert the birth date to an integer value.
int convertDateToValue(const string& date) {
    int month, day;

    // I used stringstream for easy parsing of the date string.
    std::stringstream ss(date);
    char delimiter;

    // This is to parse the date as month-day format.
if (!(ss >> month >> delimiter >> day) ||
    delimiter != '-' ||
    month < 1 || month > 12 ||
    day < 1 || day > 31) {

/* If parsing fails or the month and day values are out of range,
 return a special value to indicate an invalid date.*/
        return -1;
    }

    /* Perform additional validation based on the month and day
     (you can adjust these conditions as needed).*/
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        // Months with 30 days.
        return -1;
    } else if (month == 2) {
        if (day > 29) {
            // February, check for leap year.
            return -1;
        }
    }

// This is to convert the date to a single integer value.
    int dateValue = month * 100 + day;
    return dateValue;
}


string findZodiacSign(const string& birthDate) {
// Arranged well so that the program can read from zodiacDateRanges properly.
// If not arranged properly will output mixed up and wrong zodiacs to user.
    vector<string> zodiacSignNames;
zodiacSignNames.push_back("Aries");
zodiacSignNames.push_back("Taurus");
zodiacSignNames.push_back("Capricorn");
zodiacSignNames.push_back("Libra");
zodiacSignNames.push_back("Sagittarius");
zodiacSignNames.push_back("Leo");
zodiacSignNames.push_back("Aquarius");
zodiacSignNames.push_back("Cancer");
zodiacSignNames.push_back("Pisces");
zodiacSignNames.push_back("Virgo");
zodiacSignNames.push_back("Scorpio");
zodiacSignNames.push_back("Gemini");
    vector<string> zodiacDateRanges;
zodiacDateRanges.push_back("03-21 to 04-14");
zodiacDateRanges.push_back("04-20 to 05-20");
zodiacDateRanges.push_back("12-22 to 01-19");
zodiacDateRanges.push_back("09-23 to 10-22");
zodiacDateRanges.push_back("11-22 to 12-21");
zodiacDateRanges.push_back("07-23 to 08-22");
zodiacDateRanges.push_back("01-20 to 02-18");
zodiacDateRanges.push_back("06-21 to 07-22");
zodiacDateRanges.push_back("02-19 to 03-20");
zodiacDateRanges.push_back("08-23 to 09-22");
zodiacDateRanges.push_back("10-23 to 11-21");
zodiacDateRanges.push_back("05-21 to 06-20");

    // This is to convert the birth date to an integer value.
    int birthDateValue = convertDateToValue(birthDate);
if (birthDateValue != -1) {
    // This is to enable it coverts dates properly.
    for (size_t i = 0; i < zodiacDateRanges.size(); ++i) {
        size_t hyphenPos = zodiacDateRanges[i].find(" to ");
        // Has to be "to" not "-" or it wont read the zodiac correctly
        if (hyphenPos != string::npos) {
            string startMonthDay = zodiacDateRanges[i].substr(0, hyphenPos);
            string endMonthDay = zodiacDateRanges[i].substr(hyphenPos + 4);
            int startDate = convertDateToValue(startMonthDay);
            int endDate = convertDateToValue(endMonthDay);


// This is to check if the birth date falls within the current date range.
            if ((birthDateValue >= startDate && birthDateValue <= endDate) ||
((endDate < startDate) &&
(birthDateValue >= startDate || birthDateValue <= endDate))) {
                return zodiacSignNames[i];
            }
        }
    }
    return "Invalid date. Please retry";

} else {
    return "Invalid Date. Please retry";
}
}



string getCharacteristics(const string& zodiacSign) {
    // General characteristics of Zodiacs.
    // All characteristics from cosmopolitan.com.
    if (zodiacSign == "Sagittarius") {
return "Sagittarius the sign with birth dates between 22 Nov and 21 Dec.\n"
"and belong to the Fire element of the zodiac (along with Leo and Aries).\n"
"Sagittarians are the bright, breezy, adorable 'Tiggers' of the zodiac.\n"
"all big hugs, bouncy energy and lots of laughs.\n"
"They have zero filters,\n"
"which makes them spontaneous, rude, honest, hilarious and challenging.\n"
"If you know a Sagittarian, you'll know all about this!\n"
"They'll have said things to you which ~scorched~,\n"
"but five minutes later, all is well again. You just can't stay mad at them.\n"
"Sagittarians are lively,\n"
"passionate,smart, more philosophical than their clowny energy may hint at.\n"
"They love be free and resist rules,regulations,constraints and schedules.\n"
"They just like doing what they do, when they wanna do it.\n"
"They're born travellers, adventurers, explorers and free spirits.\n"
"They are ruled by Jupiter, which makes them all jammy so-and-sos,\n"
"who (no matter how absurd an escapade they pursue) often land on their.\n"
"Sagittarians are great companions for wild weekends.\n"
"To get an idea of the classic Sagittarius personality traits and types,\n"
"we need only to look to some of the most famous archers:\n"
"Brad Pitt,Chrissy Teigen,Miley Cyrus,Taylor Swift,\n"
"Jay-Z,Britney Spears,Tyra Banks. These guys are never dull.";
    } else if (zodiacSign == "Cancer") {
return "The Cancer star signs dates are between 21st June and 22nd July\n"
"and the zodiac sign is intense, incredibly charismatic and attractive,\n"
"but also possessive and moody. They can turn on a sixpence.\n"
"Ruled by the Moon,they're passionate,creative,secretive,intuitive,caring.\n"
"Cancerians command your total loyalty and undivided attention,\n"
"but they will return it in droves. A ride or die friend and partner.\n"
"They are always interested in you,\n"
"and have a knack of getting how you truly feel, even when you don't say it.\n"
"They are mind readers! They do expect you to be fully into them too,\n"
"and go to great lengths to illicit the sympathy and interest of others.\n"
"They can be a lil' dramatic and attention-seeking tbh,\n"
"and this trait can cause them more relationship woes than they realise.\n"
"To get an idea of the classic Cancerian personality traits and types,\n"
"we need only to look to some of the most famous crabs (the sign's symbol):\n"
"Princess Diana,Ariana Grande,elena Gomez,Solange Knowles,Nicole Scherzinger\n"
"and Lindsay Lohan. All of these people wear their heart on their sleeve.";
    } else if (zodiacSign == "Pisces") {
return "Pisces have the star sign dates between 20th February - 20th March\n"
"and are ruled by the double whammy of Neptune\n"
"(psychic,esoteric planet of mystery) and Jupiter!\n"
"(lucky son-of-a-gun planet of abundance.)\n"
"So,the zodiac sign is both secretive and expansive,\n"
"magical and worldly, soulful and joyful.\n"
"Pisceans, a water sign, are worldly wise ~old souls~ \n"
"with enormous depths of compassion and empathy for others.\n"
"Pisceans' symbol in the horoscope is two fishes facing opposite directions,\n"
"this reflects the duality of their continual inner struggle.\n"
"On the one hand, they want to be successful, busy, driven and active,\n"
"but on the other hand,\n"
"they just want to pull the covers over their head and stay in bed.\n"
"Life is hard for Pisceans; they pick up on ALL the vibes.";
    } else if (zodiacSign == "Aries") {
return "The Aries star sign, born between March 21st and April 20th,\n"
 "are loud, proud, strong and brave.\n"
"They are the ~baby~ of the zodiac, only in that they are the first sign\n"
"and therefore the most ~raw~ with their needs, demands and emotions.\n"
"They can, tbf, be pretty needy. Aries command your total attention,\n"
"loyalty and capacity to entertain them. They get bored REAL fast.\n"
"Aries have a very warm and passionate nature. \n"
"Their Mars ruler makes them competitive and full-on too.\n"
"They have a big presence, they can light up a room.\n"
"And, mostly, they're lovely to be around because they genuinely care.\n"
"Just don't get into a competition with them,\n"
"because we all know how that will end up.\n"
"To get an idea of the classic Aries personality traits and types,\n"
"we need only to look to some of the most famous rams (the sign's animal):\n"
"Lady Gaga, Sarah Jessica Parker, Mariah Carey\n"
"and Chance the Rapper to name a few.\n"
"This lot likes winning, getting attention and being on top.";
    } else if (zodiacSign == "Taurus") {
return "What do you know about Taurus traits?It's a misunderstood star sign.\n"
"Many people think of Taureans as laidback,even lazy,and extremely stubborn.\n"
"Sure, they CAN come off like this sometimes,\n"
"but actually those behaviours are driven by a more intellectual\n"
"also very analytical nature than they're credited with.\n"
"People who are Taurus, born between April 21 and May 21,\n"
"ponder deeply on all matters - \n"
"love, life, money, work, the weather, last year's Love Island.\n"
"They deconstruct situations carefully, \n"
"pull them apart to understand how things work and what makes people tick.\n"
"This takes a while (hence them seeming lazy) \n"
"and when it's done means that their conclusions are thorough and rock-solid\n"
"(hence why they seem stubborn, because they know their own mind).\n"
"To get an idea of the classic Taurean personality traits and types,\n"
"we need to look to some of the famous bulls (the sign's spirit animal): \n"
"Adele, Rami Malek, David Beckham, Queen Elizabeth,\n"
"Kelly Clarkson, Cate Blanchett and Cher to name a few.\n"
"Taureans can be gentle and they can be fierce,they don't like to be pushed,\n"
"they have strong opinions, and they love their home comforts.";
    } else if (zodiacSign == "Gemini") {
return "Gemini is the star sign born between May 22 and June 22,\n"
"and belong to the Air element of the zodiac (along with Libra and Aquarius).\n"
"Their main Gemini traits are being super-fast, super-smart, super-adaptable\n"
"and also super-curious people.\n"
"All of this super-ness makes them fascinating to be around,\n"
"albeit usually only for short spells because they can a) wear you out, b)\n"
"get easily distracted elsewhere and before you know it, they're off.\n"
"Geminis like variety, keeping their options open, \n"
"having lots of opportunities on the go, \n"
"and being ~in the know~ about anything, everything, and everyone.\n"
"Notorious gossips! They are generally kind, \n"
"but there is a slither of chilliness and detachment, \n"
"created by their Air element and twin nature.\n"
"You never quite know which Gemini is showing up, \n"
"and there's always one in the background taking notes, and keeping secrets.\n"
"To get an idea of the classic Gemini personality traits and types,\n"
"we need to look to some of the most famous twins(the star sign's symbol):\n"
"Kanye West, Kylie Minogue, Tupac, Marilyn Monroe, /n"
"Angelina Jolie and Donald Trump (sorry) to name a few.\n"
"These guys ALL have big personalities.";
    } else if (zodiacSign == "Leo") {
return "Leos are the star sign born between 23rd July 23 and 22nd August\n"
"and are also ruled by the Sun.\n"
"This perfectly represents their innate belief that......\n"
"they are the centre-of-the-universe! That sounds annoying AF (it can be),\n"
"but you'll be happy to let them take the stage cause they work hard for it.\n"
"This sign of the zodiac is charming, warm, welcoming, funny, protective, \n"
"and generally great company.\n"
"Leos love to lead, perform, talk, be admired \n"
"and genrally love to receive the praise and respect of others.\n"
"They are naturally regal, \n"
"and always assume a boss-like stance in any relationship or group dynamic.\n"
"They are confident, bright and sexy people, though they can be jealous, \n"
"they can also be controlling and possessive at their worst.\n"
"To get an idea of the classic Leo personality traits and types,\n"
"we need only to look to some of the most famous lions (the sign's symbol):\n"
"Madonna, Jennifer Lopez, Kylie Jenner, Sandra Bullock.";
    } else if (zodiacSign == "Virgo") {
return "Virgos is the star sign born between August 23 and September 22,\n"
"look like a swan, all elegant and serene, \n"
"but underneath their ~paddlers~ are paddling furious.\n"
"This zodiac sign works HARD at coming off all effortless and perfect.\n"
"They have extremely high standards, none more so than for themselves,\n"
"and they  actually doobsess over everything LOL.\n"
"They are fantastic detail-people, love organising stuff, \n"
"and can be relied on to make everything go smoothly.\n"
"Virgos can come off as uptight or critical, \n"
"but their Mercury ruler does present a lighter side to their character.\n"
"They love gossip, information, education, entertainment.\n"
"Their mind is sharp, bright and shrewd. Virgos make great friends, \n"
"they are 100 percent solid and also (secretly) naughty fun.\n"
"To get an idea of the classic Virgo personality traits and types, \n"
"we need only to look to some of the most famous virgins (the sign's symbol\n"
"- not literal)- Beyonce, Pink, Keanu Reeves, Cameron Diaz, and Blake Lively.";

    } else if (zodiacSign == "Libra") {
return "Librans are the slick, smart, charmers of the zodiac.\n"
"Their star sign dates are between September 23 and October 22,\n"
"and belong to the Air element of the zodiac(also with Gemini and Aquarius).\n"
"Always tactful, pleasing and diplomatic \n"
"- they can fit in anyplace, anytime, with anyone.\n"
"Shape-shifting is almost a sport to Libra, \n"
"and they enjoy mingling and socialising with different squads and crews.\n"
"You can find them lounging and flirting anywhere \n"
"- being the centre of attention and loved by all around.\n"
"Libras love to think, analyse, ponder and dissect stuff, \n"
"which makes them champion procrastinators too.\n"
"They love to take an objective viewpoint,find the best solution to issues,\n"
"and enjoy learning new information. They need mental stimulus.\n"
"They hate mess, chaos, disorder and conflict, \n"
"and that is where their uber-diplomacy comes in real handy.\n"
"To get an idea of the classic Libran personality traits and types,\n"
"we need only to look to some of the most famous autumn babies:\n"
"Kim Kardashian,Serena Williams,Bella Hadid,Cardi B,Gwen Stefani and Halsey.";
    } else if (zodiacSign == "Scorpio") {
return "Scorpios' star sign dates are between October 23 and November 21,\n"
"and belong to Water element of the zodiac(along with Cancer and Pisces).\n"
"Scorpios are strong, enigmatic, independent characters\n"
"who crackle with an intensity and charisma that makes them un-ignorable.\n"
"For all of that power though, they often remain un-knowable to others,\n"
"because they guard themselves and their private lives fiercely.\n"
"You can bet there's something juicy going on, under the wraps,\n"
"though, because Scorpios like extremes, challenges, danger and darkness.\n"
"They are, because of their planetary ruler Pluto,\n"
"drawn to the outliers of human experience.\n"
"If it's kinky, risky or thrilling, a Scorpio will be involved somehow!\n"
"Scorpios are loyal, smart, shrewd and stoic. They stand by their beliefs,\n"
"and they don't crave anyone else's approval.\n"
"Scorpio is like the big, bad elder sister of the Water sign crew.\n"
"You don't mess with the turbulent, \n"
"deadly scorpion my friend, their sting can be fatal.\n"
"And they make the other signs of the zodiac \n"
"(apart from maybe Aries, who they share a planetary influence with)....\n"
"look like  absolute wusses! haha\n"
"To get an idea of the classic Scorpio personality traits and types,\n"
"we need only to look to some of the most famous Halloween children: Drake,\n"
"Kendall Jenner, Emma Stone, Ryan Reynolds and Ciara.";
    } else if (zodiacSign == "Capricorn") {
return "Capricorn star sign dates between 22nd December and 20th January.\n"
"And belong to the Earth element of the zodiac \n"
"(with Taurus and Virgo who are incredibly compatible with,romantically).\n"
"The Earth sign crew are all practical, self reliant, stoic and ambitious.\n"
"You'd want them in your corner... but maybe not at a party.\n"
"Capricorns - the hardest workers of the zodiac,love getting ahead in life.\n"
"They are ambitious, determined, materialistic and strong. \n"
"They will keep going when others would've given up ten miles back.\n"
"This makes them great partners in life,as well as friends or collaborators.\n"
"Capricorns tend to keep small circles, \n"
"but are loyal and supportive of their friends and loved ones.\n"
"They love creating secure, luxurious nests and living a comfortable.\n"
"Living well is important to them.\n"
"Capricorns are born shrewd, they get what makes others tick, \n"
"and they are also very self-aware of their own needs and traits too.\n"
 "Caps are good people!\n"
"To get an idea of the classic Capricorn personality traits and types,\n"
"we need only to look to some of the most famous celeb Capricorns:\n"
"Kate Middleton, Michelle Obama, Dolly Parton, Bradley Cooper, Zayn Malik,\n"
"John Legend and Liam Hemsworth,Yep, you Caps are in good company.";

    } else if (zodiacSign == "Aquarius") {
return "Aquarians have star sign dates between January 21 and February 19,\n"
"and belong to the Air element of the zodiac \n"
"(along with Gemini and Libra,they have romantic compatibility with).\n"
"Aquarians are ruled by Uranus, which is the planet of invention,\n"
"also: innovation, space travel and aerodynamics.\n"
"Aquarians not only want to save the world, \n"
"they have engineering and intellectual smarts and always have a plan.\n"
"Aquarius's symbol is the water bearer, which many believe represents the...\n"
"gifts of truth and pure intentions that they bring to the world.\n"
"Aquarians are very upfront people, \n"
"and they don't do shenanigans or shady business.\n"
"They tell you how it is and feel no two ways about it,if you don't like it.\n"
"Some people find them aloof or cold, \n"
"but they just keep their emotions more buttoned down than most.\n"
"To get an idea of the classic Aquarius personality traits and types, \n"
"we need only to look to some famous Aquarians: Harry Styles, Alicia Keys,\n"
"Kerry Washington,Jennifer Aniston,Shakira and Oprah Winfrey to name a few.\n"
 "This lot dance to their own beat, for sure.";
    } else {
        return "Invalid zodiac entered. Please retry";
    }
}

string getZodiacSymbol(const string& zodiacSign) {
    // Description of zodiac symbol.
    if (zodiacSign == "Sagittarius") {
return "symbol of saggitarius is a centaur that has a name:\n"
"intrestingly named Chiron holding a bow and arrow.";
    } else if (zodiacSign == "Cancer") {
return "The sideways 6's and/or 9's of the symbol of Cancer:\n"
" they are actually thought to represent crab claws.";
    } else if (zodiacSign == "Capricorn") {
return "The symbol of capricorn is said to represent a sea goat:\n"
"which is a mythical creature said to be half-goat and half-fish.";
    } else if (zodiacSign == "Aquarius") {
return "The squiggly lines of Aquarius symbol are said to represent water.";
    } else if (zodiacSign == "Pisces") {
return "The symbol of Pisces is thought to represent:\n"
"two fish tied together by a rope swimming in opposite directions.";
    } else if (zodiacSign == "Aries") {
        return "The symbol of Aries is said to represent the head of a ram.";
    } else if (zodiacSign == "Taurus") {
return "The circle with horns symbol of Taurus:\n"
"is apparently said to represent the head of a bull.";
    } else if (zodiacSign == "Gemini") {
return "The symbol of Gemini is the Roman numeral for the number two:\n"
"known to represent the Gemini twins (two people). Very interesting.";
    } else if (zodiacSign == "Leo") {
return "The symbol of Leo: thought to depict a simplified drawing of a lion.";
    } else if (zodiacSign == "Virgo") {
return "The curly M of Virgo has many theories behind it:\n"
"Some common guesses are that the symbol.....\n"
"is an M for maiden represents a virgin with crossed legs,\n"
"other common guesses are that it depicts human intestines.";
    } else if (zodiacSign == "Libra") {
return "The symbol of Libra: \n"
" It is said to depict either a setting sun or a pair of scales.";
    } else if (zodiacSign == "Scorpio") {
        return "The symbol of Scorpio is said to represent a scorpion.";
    } else {
        return "Invalid zodiac sign entered. Please retry.";
    }
}
// Zodiac app completed.
