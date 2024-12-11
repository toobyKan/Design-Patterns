#include <iostream>
class ProvideInternet{
    public:
        virtual void provideImp() = 0; 
        virtual ~ProvideInternet(){};
};

class WifiProvide : public ProvideInternet{
    public:
        void provideImp() override
        {
            std::cout << "WiFi\n";
        }
};

class Ethernet : public ProvideInternet{
    public:
        void provideImp() override
        {
            std::cout << "Ethernet\n";
        }
};

class InternetProvider{
    protected:
        ProvideInternet* provideInternet;
    public:
        virtual ~InternetProvider(){};
        InternetProvider(ProvideInternet* provideInt) : provideInternet(provideInt)
        {}
        virtual void provide()
        {
            this->provideInternet->provideImp();
        }
};

class WiFi : public InternetProvider{
    public: 
        WiFi(ProvideInternet* provideInternet) : InternetProvider(provideInternet)
        {}
        void provide() override
        {
             this->provideInternet->provideImp();
        }
};

class GPON : public InternetProvider{
    public: 
        GPON(ProvideInternet* provideInternet) : InternetProvider(provideInternet)
        {}
        void provide() override
        {
             this->provideInternet->provideImp();
        }
};


int main(){
    
    ProvideInternet* provideInt1= new  WifiProvide;
    InternetProvider* providerWiFi = new InternetProvider(provideInt1);
    providerWiFi->provide();
    delete provideInt1;
    delete providerWiFi;
    
    ProvideInternet* provideInt2= new  Ethernet;
    InternetProvider* providerGPON = new InternetProvider(provideInt2);
    providerGPON->provide();
    delete provideInt2;
    delete providerGPON;
    
    return 0;
}
