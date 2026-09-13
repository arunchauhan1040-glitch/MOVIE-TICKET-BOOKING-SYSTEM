# Class Diagram

```mermaid
classDiagram
    class Movie {
      -int id
      -string title
      -string language
      -int durationMinutes
    }
    class Seat {
      -int number
      -SeatType type
    }
    class Screen {
      -int id
      -string name
      -vector~Seat~ seats
    }
    class Cinema {
      -int id
      -string name
      -vector~Screen~ screens
    }
    class ShowSeat {
      -Seat* seat
      -SeatStatus status
    }
    class Show {
      -int id
      -Movie* movie
      -Screen* screen
      -string startTime
      -vector~ShowSeat~ showSeats
    }
    class Customer {
      -int id
      -string name
      -string phone
    }
    class Booking {
      -static int nextBookingId
      -int id
      -Customer* customer
      -Show* show
      -vector~ShowSeat*~ seats
      -double total
      -string paymentMethod
      -string status
    }
    class Payment {
      <<abstract>>
      +pay(double) bool
      +method() string
    }
    class UPIPayment
    class CardPayment
    class CashPayment
    class PriceCalculator
    class TicketPrinter
    class BookingService

    Cinema *-- Screen
    Screen *-- Seat
    Show *-- ShowSeat
    Show o-- Movie
    Show --> Screen
    ShowSeat --> Seat
    Booking --> Customer
    Booking --> Show
    Booking --> ShowSeat
    Payment <|-- UPIPayment
    Payment <|-- CardPayment
    Payment <|-- CashPayment
    BookingService --> Booking
    BookingService --> Payment
    BookingService --> PriceCalculator
    BookingService --> TicketPrinter
```

## Relationships
- **Composition:** Cinema–Screen, Screen–Seat, Show–ShowSeat.
- **Aggregation:** Show uses a Movie that can exist independently.
- **Association:** Booking is associated with Customer and Show.
- **Runtime polymorphism:** Payment subclasses override `pay()` and `method()`.
- **Compile-time polymorphism:** overloaded Movie constructors and PriceCalculator methods.
