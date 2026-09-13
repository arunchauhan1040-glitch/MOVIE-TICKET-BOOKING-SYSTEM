# MOVIE-TICKET-BOOKING-SYSTEM

A modular, menu-driven C++ Movie Ticket Booking System developed for the TCS-504 System Design Assignment. It covers movie/show listing, seat availability, booking, tier-based pricing, UPI/Card/Cash payments, ticket generation, cancellation, OOP concepts, SOLID principles, validation, and edge cases.

## Features
- List movies and shows
- Display available/booked seats
- Book multiple seats in one transaction
- Silver / Gold / Platinum tier pricing
- UPI, Card, and Cash payments
- Payment-failure rollback of selected seats
- Ticket generation with booking details
- Booking cancellation with seat release
- Duplicate, invalid, unavailable-seat, and invalid-payment validation

## Project Structure
- `main.cpp` — executable menu and application flow
- `Movie.cpp` — Movie domain class
- `Seat.cpp` — Seat domain class and seat enums
- `Screen.cpp` — screen and seat composition
- `Cinema.cpp` — cinema and screen composition
- `ShowSeat.cpp` — per-show seat availability state
- `Show.cpp` — show domain class
- `Customer.cpp` — customer domain class
- `Booking.cpp` — booking entity and static booking ID
- `Payment.cpp` — abstract payment interface
- `UPIPayment.cpp` / `CardPayment.cpp` / `CashPayment.cpp` — payment implementations
- `PriceCalculator.cpp` — tier-based fare calculation
- `TicketPrinter.cpp` — ticket presentation
- `BookingService.cpp` — booking/cancellation orchestration
- `DESIGN.md` — OOP, SOLID, validation and build notes
- `docs/CLASS_DIAGRAM.md` — class diagram
- `docs/SEQUENCE_DIAGRAM.md` — booking and cancellation sequence diagrams

## OOP & Design Concepts
Encapsulation, Abstraction, Inheritance, Runtime Polymorphism, Compile-Time Polymorphism, Static Members, `this` keyword, Composition, Aggregation, Association, and SOLID principles.

## Build & Run

The project intentionally uses one class per `.cpp` file and no header files. `main.cpp` includes the implementation files in dependency order.

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o movie_booking
./movie_booking
```

No external libraries are required.
