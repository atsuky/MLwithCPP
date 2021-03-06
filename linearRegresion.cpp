#include <iostream> 
#include <vector> 
#include <tuple>
#include <numeric>
#include <cmath>
#include <limits>

using namespace std;

class LinearRegression{
public:
    LinearRegression() {}
    ~LinearRegression() {}

    LinearRegression(vector<double> & m_x_vals_, vector<double> & m_y_vals_) : m_x_vals(m_x_vals_), 
    m_y_vals(m_y_vals_), m_num_elems(m_y_vals_.size()), m_old_error(std::numeric_limits<double>::max()) {}

    void trainAlgorithm(int num_iters_, double a_init, double b_init) {
       
        int iter = 0;
        m_a = a_init;
        m_b = b_init;

        while (!isConverged() && iter < num_iters_){
            //inicialitzar valors
            double step = 0.02;
            double a_grad = 0.0;
            double b_grad = 0.0;

            //Computar gradient respecte a
            for (int i = 0; i < m_num_elems; ++i){
                a_grad += m_x_vals[i] * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
            }
            a_grad = (2 * a_grad) / m_num_elems;

            //Computar respecte b 
            for (int i = 0; i < m_num_elems; ++i){
                b_grad += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
            }
            b_grad = (2 * b_grad) / m_num_elems;

            //Take Step

            m_a -= (step * a_grad);
            m_b -= (step * b_grad);

            cout << "a:   " << m_a << " , b:  " << m_b << endl;
            cout << "grad_a:   " << a_grad << " , grad_b:  " << b_grad << endl;

            ++iter;
        }
    }

    double regress(double x_){
        double res = m_a * x_ + m_b;
        return res;
    }

private:

    bool isConverged(){
        double error = 0;
        double thresh = 0.001;

        for (int i = 0; i < m_num_elems; ++i){
	     error += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]) * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
	}

        error /= m_num_elems;
        cout << "Error" << error << endl;
        bool res = (abs(error) > m_old_error - thresh && abs(error) < m_old_error + thresh) ? true : false;
	m_old_error = abs(error);
	cout << res << endl;
	return res;
    }

    vector<double> m_y_vals;
    vector<double> m_x_vals;
    double m_num_elems, m_a, m_b, m_old_error;

};

int main (int argc, char ** argv){

    vector<double> y({2.8,2.9,7.6,9,8.6});
    vector<double> x({1,2,3,4,5,});

    LinearRegression lr(x,y);

    lr.trainAlgorithm(1000, 3, -10);

    cout << lr.regress(3) << endl;

    return 1;
}

