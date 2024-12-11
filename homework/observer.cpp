#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
class Observer;

template <typename T>
class Observable {
    std::vector<Observer<T> *> observers;

    public:
        void subscribe(Observer<T> *observer) { observers.push_back(observer); }
        void unsubscribe(Observer<T> *observer) {
            auto it = std::find(observers.begin(), observers.end(), observer);
            if (it != observers.end())
                observers.erase(it);
        }
        void notify(T &source, const std::string &fieldName, const std::string &newValue) {
            for (auto observer : observers) {
                observer->fieldChanged(source, fieldName, newValue);
            }
        }
};

// Publisher - Concrete Observable
class Stock : public Observable<Stock> {
    std::string ticker;
    float price;

    public:
        Stock(const std::string &tickerSymbol, float initialPrice) : ticker(tickerSymbol), price(initialPrice) {}

        std::string getTicker() const { return ticker; }
        float getPrice() const { return price; }

        void setPrice(float newPrice) {
            if (this->price == newPrice)
                return;
            price = newPrice;
            notify(*this, "Price", std::to_string(newPrice));
        }
};

// Observer
template <typename T>
class Observer {
    public:
        virtual void fieldChanged(T &source, const std::string &fieldName, const std::string &newValue) = 0;
};

// Concrete Observer 1: Investor
class Investor : public Observer<Stock> {
    std::string name;

    public:
        Investor(const std::string &investorName) : name(investorName) {}

        void fieldChanged(Stock &stock, const std::string &fieldName, const std::string &newValue) override {
            if (fieldName == "Price") {
                std::cout << name << " notified: Stock " << stock.getTicker() << " price updated to $" << newValue << std::endl;
            }
        }
};

// Concrete Observer 2: News Agency
class NewsAgency : public Observer<Stock> {
    public:
        void fieldChanged(Stock &stock, const std::string &fieldName, const std::string &newValue) override {
            if (fieldName == "Price") {
                std::cout << "Breaking News: Stock " << stock.getTicker() << " price is now $" << newValue << std::endl;
            }
        }
};

int main() {
    Stock appleStock("AAPL", 150.0f);

    Investor alice("Alice");
    Investor bob("Bob");
    NewsAgency cnn;

    appleStock.subscribe(&alice);
    appleStock.subscribe(&bob);
    appleStock.subscribe(&cnn);

    std::cout << "Initial Stock Price Updates:" << std::endl;
    appleStock.setPrice(155.0f);
    appleStock.setPrice(160.0f);

    std::cout << "\nUnsubscribing Bob..." << std::endl;
    appleStock.unsubscribe(&bob);

    appleStock.setPrice(165.0f);

    return 0;
}
