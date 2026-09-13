#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

// The assignment intentionally uses one class per .cpp file and no header files.
// These source files are included here to form one translation unit.
#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "UPIPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

static void line() { cout << "\n--------------------------------------------------\n"; }

static int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        int value;
        char extra;
        if (ss >> value && !(ss >> extra)) return value;
        cout << "Invalid input. Please enter a number.\n";
    }
}

static double readDouble(const string& prompt) {
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        double value;
        char extra;
        if (ss >> value && !(ss >> extra) && value >= 0) return value;
        cout << "Invalid amount.\n";
    }
}

static string readString(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

static Movie* findMovie(vector<Movie>& movies, int id) {
    for (auto& movie : movies) if (movie.getId() == id) return &movie;
    return nullptr;
}

static Show* findShow(vector<Show>& shows, int id) {
    for (auto& show : shows) if (show.getId() == id) return &show;
    return nullptr;
}

static Booking* findBooking(vector<unique_ptr<Booking>>& bookings, int id) {
    for (auto& booking : bookings)
        if (booking && booking->getId() == id) return booking.get();
    return nullptr;
}

static void listMovies(const vector<Movie>& movies) {
    line();
    cout << "NOW SHOWING\n";
    for (const auto& movie : movies) {
        cout << "ID: " << movie.getId() << " | " << movie.getTitle()
             << " | " << movie.getLanguage() << " | " << movie.getDuration() << " min\n";
    }
}

static void listShows(const vector<Show>& shows) {
    line();
    cout << "AVAILABLE SHOWS\n";
    for (const auto& show : shows) {
        cout << "Show ID: " << show.getId()
             << " | Movie: " << show.getMovie()->getTitle()
             << " | Screen: " << show.getScreen()->getName()
             << " | Time: " << show.getStartTime() << "\n";
    }
}

static void displaySeats(Show& show) {
    line();
    cout << "SEAT MAP - " << show.getMovie()->getTitle()
         << " | " << show.getScreen()->getName() << "\n";
    for (const auto& seat : show.getShowSeats()) {
        cout << setw(3) << seat.getNumber() << "["
             << (seat.isAvailable() ? "AVAILABLE" : "BOOKED") << "] "
             << seat.typeName() << "\n";
    }
}

static unique_ptr<Payment> createPayment() {
    cout << "\n1. UPI\n2. Card\n3. Cash\n";
    int choice = readInt("Payment method: ");
    if (choice == 1) {
        string upi = readString("UPI ID (example@upi): ");
        return make_unique<UPIPayment>(upi);
    }
    if (choice == 2) {
        string card = readString("16-digit card number: ");
        return make_unique<CardPayment>(card);
    }
    if (choice == 3) {
        double cash = readDouble("Cash received: Rs.");
        return make_unique<CashPayment>(cash);
    }
    cout << "Invalid payment method.\n";
    return nullptr;
}

int main() {
    // Stable storage is reserved before pointers/references are shared.
    vector<Movie> movies;
    movies.reserve(3);
    movies.emplace_back(1, "Interstellar", "English", 169);
    movies.emplace_back(2, "3 Idiots", "Hindi", 170);
    movies.emplace_back(3, "Inception", "English", 148);

    Cinema cinema(1, "CineStar Multiplex");
    cinema.addScreen(Screen(1, "Screen 1", 6, 6, 4));
    cinema.addScreen(Screen(2, "Screen 2", 5, 7, 4));

    vector<Show> shows;
    shows.reserve(6);
    shows.emplace_back(101, &movies[0], &cinema.getScreens()[0], "10:00 AM");
    shows.emplace_back(102, &movies[0], &cinema.getScreens()[0], "06:30 PM");
    shows.emplace_back(103, &movies[1], &cinema.getScreens()[1], "01:30 PM");
    shows.emplace_back(104, &movies[1], &cinema.getScreens()[1], "08:00 PM");
    shows.emplace_back(105, &movies[2], &cinema.getScreens()[0], "03:00 PM");

    vector<unique_ptr<Booking>> bookings;
    BookingService bookingService;

    Customer customer(1, "Guest Customer", "9999999999");

    cout << "\n===============================================\n";
    cout << "      MOVIE TICKET BOOKING SYSTEM\n";
    cout << "===============================================\n";

    while (true) {
        cout << "\nMENU\n"
             << "1. List Movies\n"
             << "2. List Shows\n"
             << "3. Check Seat Availability\n"
             << "4. Book Tickets\n"
             << "5. View Ticket\n"
             << "6. Cancel Booking\n"
             << "7. View My Bookings\n"
             << "8. Exit\n";

        int choice = readInt("Choose option: ");

        if (choice == 1) {
            listMovies(movies);
        } else if (choice == 2) {
            listShows(shows);
        } else if (choice == 3) {
            int showId = readInt("Enter show ID: ");
            Show* show = findShow(shows, showId);
            if (!show) cout << "Show not found.\n";
            else displaySeats(*show);
        } else if (choice == 4) {
            listShows(shows);
            int showId = readInt("Enter show ID: ");
            Show* show = findShow(shows, showId);
            if (!show) {
                cout << "Show not found.\n";
                continue;
            }

            displaySeats(*show);
            int count = readInt("How many seats? ");
            if (count <= 0 || count > 10) {
                cout << "Choose between 1 and 10 seats.\n";
                continue;
            }

            vector<int> seatNumbers;
            for (int i = 0; i < count; ++i)
                seatNumbers.push_back(readInt("Seat " + to_string(i + 1) + " number: "));

            auto payment = createPayment();
            if (!payment) continue;

            Booking* booking = bookingService.book(&customer, show, seatNumbers, *payment);
            if (booking) {
                bookings.emplace_back(booking);
                cout << "Booking confirmed successfully.\n";
            } else {
                cout << "Booking failed. Check seat selection and payment details.\n";
            }
        } else if (choice == 5) {
            int bookingId = readInt("Booking ID: ");
            Booking* booking = findBooking(bookings, bookingId);
            if (!booking) cout << "Booking not found.\n";
            else TicketPrinter().print(*booking, booking->getPaymentMethod());
        } else if (choice == 6) {
            int bookingId = readInt("Booking ID to cancel: ");
            Booking* booking = findBooking(bookings, bookingId);
            if (!booking) {
                cout << "Booking not found.\n";
            } else if (bookingService.cancel(booking)) {
                cout << "Booking cancelled. Seats are available again.\n";
            } else {
                cout << "Cancellation failed. Only confirmed bookings can be cancelled.\n";
            }
        } else if (choice == 7) {
            line();
            cout << "MY BOOKINGS\n";
            if (bookings.empty()) cout << "No bookings yet.\n";
            for (const auto& booking : bookings) {
                cout << "Booking " << booking->getId()
                     << " | " << booking->getShow()->getMovie()->getTitle()
                     << " | Seats: " << booking->getSeats().size()
                     << " | Rs." << booking->getTotal()
                     << " | " << booking->getStatus() << "\n";
            }
        } else if (choice == 8) {
            cout << "Thank you for using Movie Ticket Booking System.\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
    return 0;
}
