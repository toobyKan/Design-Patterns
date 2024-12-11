#include <iostream>
#include <string>

class State {
    public:
        virtual void insertCard() = 0;
        virtual void enterPin(int pin) = 0;
        virtual void withdrawCash(int amount) = 0;
        virtual void ejectCard() = 0;
        virtual ~State() = default;
};

// Context
class ATM {
    State *state;

    public:
        ATM() { setState(new NoCardState(this)); }
        void setState(State *st) { state = st; }
        void insertCard() { state->insertCard(); }
        void enterPin(int pin) { state->enterPin(pin); }
        void withdrawCash(int amount) { state->withdrawCash(amount); }
        void ejectCard() { state->ejectCard(); }
};

class NoCardState : public State {
    ATM *atm;

    public:
        NoCardState(ATM *atm) : atm(atm) {}

        void insertCard() override {
            std::cout << "Card inserted. Please enter your PIN.\n";
            atm->setState(new HasCardState(atm));
        }

        void enterPin(int pin) override {
            std::cout << "No card inserted. Insert a card first.\n";
        }

        void withdrawCash(int amount) override {
            std::cout << "No card inserted. Insert a card first.\n";
        }

        void ejectCard() override {
            std::cout << "No card to eject.\n";
        }
};

class HasCardState : public State {
    ATM *atm;

    public:
        HasCardState(ATM *atm) : atm(atm) {}

        void insertCard() override {
            std::cout << "Card is already inserted.\n";
        }

        void enterPin(int pin) override {
            if (pin == 1234) {
                std::cout << "PIN correct. You can withdraw cash.\n";
                atm->setState(new AuthenticatedState(atm));
            } 
            else {
                std::cout << "Incorrect PIN. Try again.\n";
            }
        }

        void withdrawCash(int amount) override {
            std::cout << "Enter PIN before withdrawing cash.\n";
        }

        void ejectCard() override {
            std::cout << "Card ejected.\n";
            atm->setState(new NoCardState(atm));
        }
};

class AuthenticatedState : public State {
    ATM *atm;

    public:
        AuthenticatedState(ATM *atm) : atm(atm) {}

        void insertCard() override {
            std::cout << "Card is already inserted.\n";
        }

        void enterPin(int pin) override {
            std::cout << "PIN already entered.\n";
        }

        void withdrawCash(int amount) override {
            if (amount > 0 && amount <= 500) {
                std::cout << "Dispensing $" << amount << ".\n";
                atm->setState(new NoCardState(atm));
            } 
            else {
                std::cout << "Invalid amount or exceeds limit.\n";
            }
        }

        void ejectCard() override {
            std::cout << "Card ejected.\n";
            atm->setState(new NoCardState(atm));
        }
};

int main() {
    ATM atm;

    atm.insertCard();
    atm.enterPin(1234);
    atm.withdrawCash(200);

    atm.insertCard();
    atm.enterPin(9999);
    atm.ejectCard();

    atm.insertCard();
    atm.enterPin(1234);
    atm.withdrawCash(600);

    return 0;
}
