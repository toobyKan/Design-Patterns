#include <iostream>

class Vehicle {
public:
    Vehicle() = default;
    
    void set_wheels(int wheels) {
        this->wheels = wheels;
    }
    void set_engine(int engine) {
        this->engine = engine;
    }
    void set_doors(int doors) {
        this->doors = doors;
    }
    void set_seats(int seats) {
        this->seats = seats;
    }
    void set_color(const std::string& color) {
        this->color = color;
    }

    void print() {
        std::cout << "Wheels: " << wheels << "\n";
        std::cout << "Engine: " << engine << "\n";
        std::cout << "Doors: " << doors << "\n";
        std::cout << "Seats: " << seats << "\n";
        std::cout << "Color: " << color << "\n";
    }

private:
    int wheels{0};
    int engine{0};
    int doors{0};
    int seats{0};
    std::string color;
};

class Car : public Vehicle {
public:
    Car() = default;
};

class Motorcycle : public Vehicle {
public:
    Motorcycle() = default;
};

class VehicleBuilder {
public:
    virtual void build_wheels() = 0;
    virtual void build_engine() = 0;
    virtual void build_doors() = 0;
    virtual void build_seats() = 0;
    virtual void build_color() = 0;
};

class CarBuilder : public VehicleBuilder {
private:
    Car* vehicle;
public:
    CarBuilder() {
        vehicle = new Car();
    }

    void build_wheels() override {
        this->vehicle->set_wheels(4);
    }
    void build_engine() override {
        this->vehicle->set_engine(1);
    }
    void build_doors() override {
        this->vehicle->set_doors(4);
    }
    void build_seats() override {
        this->vehicle->set_seats(5);
    }
    void build_color() override {
        this->vehicle->set_color("Red");
    }

    Car* get_vehicle() {
        return vehicle;
    }
};

class MotorcycleBuilder : public VehicleBuilder {
private:
    Motorcycle* vehicle;
public:
    MotorcycleBuilder() {
        vehicle = new Motorcycle();
    }

    void build_wheels() override {
        this->vehicle->set_wheels(2);
    }
    void build_engine() override {
        this->vehicle->set_engine(1);
    }
    void build_doors() override {
        this->vehicle->set_doors(0);
    }
    void build_seats() override {
        this->vehicle->set_seats(2);
    }
    void build_color() override {
        this->vehicle->set_color("Black");
    }

    Motorcycle* get_vehicle() {
        return vehicle;
    }
};

class Director {
public:
    Car* create_car(CarBuilder* vehicleb) {
        vehicleb->build_wheels(); 
        vehicleb->build_engine(); 
        vehicleb->build_doors(); 
        vehicleb->build_seats(); 
        vehicleb->build_color();
        return vehicleb->get_vehicle(); 
    }
    
    Motorcycle* create_motorcycle(MotorcycleBuilder* vehicleb) {
        vehicleb->build_wheels(); 
        vehicleb->build_engine(); 
        vehicleb->build_doors(); 
        vehicleb->build_seats(); 
        vehicleb->build_color();
        return vehicleb->get_vehicle();
    }
};

int main() {
    Director dir;
    CarBuilder carBuilder;
    MotorcycleBuilder motorcycleBuilder;
    
    Car *car = dir.create_car(&carBuilder);
    Motorcycle *motorcycle = dir.create_motorcycle(&motorcycleBuilder);
    
    std::cout << "Car\n";
    car->print();
    
    std::cout << "\nMotorcycle\n";
    motorcycle->print();

    delete car;
    delete motorcycle;

    return 0;
}
