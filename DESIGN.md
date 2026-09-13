# TCS-504 Design Notes

## Architecture
The project is intentionally organized as one class per `.cpp` file, with no header files. `main.cpp` includes the class implementation files in dependency order and acts as the executable entry point.

## OOP Coverage
- **Encapsulation:** attributes are private and accessed through public methods.
- **Abstraction:** `Payment` is an abstract base class.
- **Inheritance:** `UPIPayment`, `CardPayment`, and `CashPayment` inherit from `Payment`.
- **Runtime polymorphism:** `BookingService` accepts `Payment&`, so the correct overridden payment method is selected at runtime.
- **Compile-time polymorphism:** overloaded `Movie` constructors and `PriceCalculator::calculate()` methods.
- **Static member:** `Booking::nextBookingId` generates unique booking IDs.
- **this keyword:** constructors use member initialization and the class design can be extended with explicit `this->` access without changing the model.
- **Composition:** Cinema owns Screens, Screen owns Seats, and Show owns ShowSeat state objects.
- **Aggregation:** a Show refers to an independently stored Movie.
- **Association:** Booking connects Customer and Show.

## SOLID Mapping
- **S — Single Responsibility:** pricing, ticket printing, booking orchestration, payment, and domain objects have separate responsibilities.
- **O — Open/Closed:** new payment methods can extend `Payment` without modifying `BookingService`.
- **L — Liskov Substitution:** each payment subclass can be used wherever a `Payment` is expected.
- **I — Interface Segregation:** the small abstract `Payment` contract exposes only payment-related operations.
- **D — Dependency Inversion:** `BookingService` depends on the `Payment` abstraction rather than a concrete payment implementation.

## Validation and Edge Cases
1. Invalid menu input is rejected.
2. Invalid show IDs are rejected.
3. Empty seat selection is rejected.
4. More than 10 seats in one booking is rejected.
5. Duplicate seat numbers are rejected.
6. Invalid seat numbers are rejected.
7. Already booked seats are rejected.
8. Failed payments release temporarily booked seats.
9. Invalid UPI IDs fail validation.
10. Invalid card numbers fail validation.
11. Insufficient cash fails validation.
12. Only confirmed bookings can be cancelled.
13. Cancellation releases seats back to AVAILABLE.

## Build

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o movie_booking
./movie_booking
```

No external libraries are required.
