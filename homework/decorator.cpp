#include <iostream>
#include <string>

class Burger{
    public:
        virtual ~Burger() = default;
        virtual std::string Serve() = 0;
        virtual float Price() = 0;
};

class ClassicBurger : public Burger{
    private:
        float m_price = 10.2;

    public:
        std::string Serve() override
        {
            return "Burger";
        }
        float Price()
        {
            return m_price;
        }
};

class BurgerDecorator : public Burger{
    protected:
        Burger *m_burger;

    public:
        BurgerDecorator(Burger *burger)
            : m_burger(burger)
        {
        }

        std::string Serve() override
        {
            return m_burger->Serve();
        }
        float Price()
        {
            return m_burger->Price();
        }
};

class Cheeseburger : public BurgerDecorator{
    private:
        float m_cheese_price = 2.8;

    public:
        Cheeseburger(Burger *burger)
            : BurgerDecorator(burger)
        {
        }
        std::string Serve() override
        {
            return m_burger->Serve() + " + cheese";
        }
        float Price()
        {
            return m_burger->Price() + m_cheese_price;
        }
};

class SpicyBurger : public BurgerDecorator{
    private:
        float m_jalapeno_price = 1.4;

    public:
        SpicyBurger(Burger *burger)
            : BurgerDecorator(burger)
        {
        }
        std::string Serve() override
        {
            return m_burger->Serve() + " + jalapeno";
        }
        float Price()
        {
            return m_burger->Price() + m_jalapeno_price;
        }
};

int main(){
    Burger *classicBurger = new ClassicBurger();
    std::cout << classicBurger->Serve() << "\n";
    std::cout << classicBurger->Price() << "\n";

    Burger *cheeseburger = new Cheeseburger(classicBurger);
    std::cout << cheeseburger->Serve() << "\n";
    std::cout << cheeseburger->Price() << "\n";

    Burger *spicyCheeseburger = new SpicyBurger(cheeseburger);
    std::cout << spicyCheeseburger->Serve() << "\n";
    std::cout << spicyCheeseburger->Price() << "\n";

    delete classicBurger;
    delete cheeseburger;
    delete spicyCheeseburger;

    return 0;
}
