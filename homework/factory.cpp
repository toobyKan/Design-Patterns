#include <iostream>
#include <cmath>

class Shape {
private:
    Shape(float area)
        : m_area(area)
    {}

    class ShapeFactory {
    public:
        static Shape makeCircle(float radius) {
            float area = M_PI * radius * radius;
            return Shape{area};
        }
        static Shape makeRectangle(float width, float height) {
            float area = width * height;
            return Shape{area};
        }
    };

public:
    static ShapeFactory shapeFactory;

    void print() {
        std::cout << "Area = " << m_area << "\n";
    }

private:
    float m_area;
};

Shape::ShapeFactory Shape::shapeFactory;

int main() 
{
    Shape circle = Shape::shapeFactory.makeCircle(4);
    circle.print();
    
    Shape rectangle = Shape::shapeFactory.makeRectangle(4, 5);
    rectangle.print();
    
    return 0;
}
