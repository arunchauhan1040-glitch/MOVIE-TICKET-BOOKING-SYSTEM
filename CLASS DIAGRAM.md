# Class Diagram

## Movie Ticket Booking System

This diagram shows the main classes, their responsibilities, relationships, multiplicities, and the payment hierarchy used in the system.

```mermaid
classDiagram
    class Cinema {
        -string name
        -vector~Screen~ screens
        +addScreen(Screen s) void
        +getScreens() vector~Screen~
        +getName() string
    }

    class Screen {
        -int screenNo
        -vector~Seat~ seats
        +addSeat(Seat s) void
        +getSeats() vector~Seat~
        +getScreenNo() int
    }

    class Seat {
        -string seatNo
        -SeatType type
        -double price
        +getSeatNo() string
        +getType() SeatType
        +getPrice() double
    }

    class Movie {
        -int id
        -string title
        -string language
        -int durationMinutes
        +Movie(int, string, string, int)
        +Movie(int, string)
        +getTitle() string
        +getLanguage() string
        +getDuration() int
    }

    class Show {
        -int showId
        -Movie* movie
        -Screen* screen
        -string startTime
        -vector~ShowSeat~ showSeats
        +getShowId() int
        +getStartTime() string
        +getMovie() Movie*
        +getScreen() Screen*
        +getShowSeats() vector~ShowSeat~
    }

    class ShowSeat {
        -Seat* seat
        -SeatStatus status
        +isAvailable() bool
        +book() bool
        +release() void
        +getSeat() Seat*
    }

    class Customer {
        -int id
        -string name
        -string phone
        +getName() string
        +getPhone() string
    }

    class Booking {
        -static int nextBookingId
        -int bookingId
        -Customer* customer
        -Show* show
        -vector~ShowSeat*~ seats
        -double totalAmount
        -BookingStatus status
        +calculateAmount() double
        +getBookingId() int
        +getStatus() BookingStatus
        +cancel() void
    }

    class Payment {
        <<abstract>>
        -double amount
        +pay(double amount) bool
    }

    class UpiPayment {
        +pay(double amount) bool
    }

    class CardPayment {
        +pay(double amount) bool
    }

    class CashPayment {
        +pay(double amount) bool
    }

    class PriceCalculator {
        +calculate(ShowSeat seat) double
        +calculate(vector~ShowSeat*~ seats) double
    }

    class TicketPrinter {
        +printTicket(Booking booking) void
    }

    class BookingService {
        -PriceCalculator* priceCalculator
        -TicketPrinter* ticketPrinter
        +bookTicket(Customer* customer, Show* show, vector~int~ seatNos, Payment* payment) void
        +cancelBooking(int bookingId) void
    }

    Cinema "1" *-- "1..*" Screen : contains
    Screen "1" o-- "1..*" Seat : has
    Movie "1" --> "1..*" Show : scheduled in
    Screen "1" --> "1..*" Show : hosts
    Show "1" *-- "1..*" ShowSeat : contains
    ShowSeat "1" --> "1" Seat : refers to
    Customer "1" --> "0..*" Booking : makes
    Booking "1" --> "1" Customer : belongs to
    Booking "1" --> "1" Show : for
    Booking "1" --> "1..*" ShowSeat : reserves
    Booking "1" ..> "1" Payment : uses
    Payment <|-- UpiPayment
    Payment <|-- CardPayment
    Payment <|-- CashPayment
    BookingService ..> Booking : creates/manages
    BookingService ..> PriceCalculator : uses
    BookingService ..> TicketPrinter : uses
    PriceCalculator ..> ShowSeat : calculates from
    TicketPrinter ..> Booking : prints
```

## Relationship Legend

| Symbol | Meaning |
|---|---|
| `*--` | Composition — strong ownership/lifecycle relationship |
| `o--` | Aggregation — weak ownership relationship |
| `-->` | Association / directed relationship |
| `..>` | Dependency / uses relationship |
| `<|--` | Inheritance / generalization |
| `1..*` | One-to-many multiplicity |
| `0..*` | Zero-to-many multiplicity |

## OOP Concepts Visible in the Design

- **Encapsulation:** class data members are private and accessed through public methods.
- **Abstraction:** `Payment` is an abstract base class.
- **Inheritance:** `UpiPayment`, `CardPayment`, and `CashPayment` inherit from `Payment`.
- **Runtime polymorphism:** `pay()` is overridden by the payment subclasses.
- **Compile-time polymorphism:** overloaded `Movie` constructors and `PriceCalculator::calculate()` methods.
- **Static member:** `Booking::nextBookingId` generates unique booking IDs.
- **Composition:** `Cinema` contains `Screen` objects and `Show` contains `ShowSeat` objects.
- **Aggregation:** `Screen` aggregates `Seat` objects.
- **Association:** `Customer`, `Booking`, `Movie`, and `Show` are connected through their relationships.
- **`this` pointer:** used by class methods/constructors where the current object is referenced.
