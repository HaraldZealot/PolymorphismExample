#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double eps = 1e-14;

struct Point
{
    double x, y;
};

class Shape
{
public:
    Shape(const string &name);
    //default copy constructor
    //default assign operator
    virtual ~Shape(){}
    virtual double getSquare()const=0;
    virtual double getPerimeter()const=0;
    string getName();
private:
    string m_name;
};

class Circle: public Shape
{
public:
    Circle(Point origin, double radius, const string &name);
    //default copy constructor
    //default assign operator
    //default destructor
    double getSquare()const;
    double getPerimeter()const;
private:
    Point  m_origin;
    double m_radius;
};

class Triangle: public Shape
{
public:
    Triangle(Point A, Point B, Point C, const string &name);
    //default copy constructor
    //default assign operator
    //default destructor
    double getSquare()const;
    double getPerimeter()const;
private:
    Point m_A, m_B, m_C;
};


void input(Shape **array,int count);
void output(Shape **array,int count);
double calcRatio(const Shape &shape);
Point input();

int main()
{
    Shape **array = 0;
    int count;
    cout<<"Enter number of shapes:\n";
    cin>>count;
    array = new Shape*[count];
    for(int i = 0; i < count; ++i)
	array[i] = 0;
    input(array, count);
    output(array, count);
    for(int i = 0; i < count; ++i)
	delete array[i];
    delete [] array;
    return 0;    
}

double calcRatio(const Shape &shape)
{
    if(fabs(shape.getPerimeter())>eps)
	return shape.getSquare()/shape.getPerimeter();
    else
	return 0.0;
}

void input(Shape **array,int count)
{
    for(int i = 0; i < count; ++i)
    {
	int selection;
	do
	{
	    cout<<"Select the type of a shype:\n";
	    cout<<"1) circle\n2) triangle\n";
	    cin>>selection;
	    string name;
	    Point O, A, B, C;
	    switch(selection)
	    {
		case 1:
		    cout<<"enter the name of the circle:\n";
		    cin>>name;
		    cout<<"enter the center of the circle:\n";
		    O=input();
		    cout<<"enter the radius of the circle:\n";
		    double radius;
		    cin>>radius;
		    array[i] = new Circle(O,radius,name);
		    break;
		case 2:
		    cout<<"enter the name of the triangle:\n";
		    cin>>name;
		    cout<<"enter the vertices of triangle\n";
		    cout<<"enter the point A:\n";
		    A=input();
		    cout<<"enter the point B:\n";
		    B=input();
		    cout<<"enter the point C:\n";
		    C=input();		    
		    array[i] = new Triangle(A, B, C, name);
		    break;
		default:
		    cerr<<"incorrect selection\n";
	    }
	}while(selection < 1 || selection > 2);
    }
}

void output(Shape **array,int count)
{
    for(int i = 0; i < count; ++i)
    {
	cout<<"The "<<i+1<<" is the "<<array[i]->getName()<<".\n";
	cout<<"It has perimeter "<<array[i]->getPerimeter()<<".\n";
	cout<<"It has square    "<<array[i]->getSquare()<<".\n";
	cout<<"The square-perimeter ratio is "<<calcRatio(*array[i])<<".\n";
	cout<<endl<<endl;
    }
}

Point input()
{
    Point result;
    cout<<"enter x coordinate:\n";
    cin>>result.x;
    cout<<"enter y coordinate:\n";
    cin>>result.y;
    return result;
}

Shape::Shape(const string &name):
    m_name(name)
{}

string Shape::getName()
{
    return m_name;
}

Circle::Circle(Point origin, double radius, const string &name):
    Shape(string("circle ")+name),
    m_origin(origin),
    m_radius(radius)
{}

double Circle::getSquare()const
{
    return M_PI*m_radius*m_radius;
}

double Circle::getPerimeter()const
{
    return 2.0*M_PI*m_radius;
}

Triangle::Triangle(Point A, Point B, Point C, const string &name):
    Shape(string("triangle ")+name),
    m_A(A),
    m_B(B),
    m_C(C)
{}

double Triangle::getSquare()const
{
    double a = sqrt((m_B.x - m_C.x) * (m_B.x - m_C.x) + (m_B.y - m_C.y) * (m_B.y - m_C.y));
    double b = sqrt((m_C.x - m_A.x) * (m_C.x - m_A.x) + (m_C.y - m_A.y) * (m_C.y - m_A.y));
    double c = sqrt((m_A.x - m_B.x) * (m_A.x - m_B.x) + (m_A.y - m_B.y) * (m_A.y - m_B.y));
    double p = getPerimeter()/2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Triangle::getPerimeter()const
{
    double a = sqrt((m_B.x - m_C.x) * (m_B.x - m_C.x) + (m_B.y - m_C.y) * (m_B.y - m_C.y));
    double b = sqrt((m_C.x - m_A.x) * (m_C.x - m_A.x) + (m_C.y - m_A.y) * (m_C.y - m_A.y));
    double c = sqrt((m_A.x - m_B.x) * (m_A.x - m_B.x) + (m_A.y - m_B.y) * (m_A.y - m_B.y));
    return a + b + c;
}