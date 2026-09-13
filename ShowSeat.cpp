class ShowSeat {
    Seat* seat;
    SeatStatus status;
public:
    explicit ShowSeat(Seat* seat) : seat(seat), status(SeatStatus::AVAILABLE) {}
    int getNumber() const { return seat->getNumber(); }
    SeatType getType() const { return seat->getType(); }
    string typeName() const { return seat->typeName(); }
    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }
    void book() { status = SeatStatus::BOOKED; }
    void release() { status = SeatStatus::AVAILABLE; }
};
