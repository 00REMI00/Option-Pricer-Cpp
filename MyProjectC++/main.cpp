#include <iostream>
#include <vector>
#include "BlackScholesPricer.h"
#include "CallOption.h"
#include "Option.h"
#include "PutOption.h"
#include "VanillaOption.h"
#include "BinaryTree.h"
#include "CRRPricer.h"
#include "DigitalCallOption.h"
#include "DigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "MT.h"

using namespace std;

int main()
{
	/*
	double s = 100.0; //prix de l'actif asset price
	double K = 100.0; //prix d'exercice de l'option strike
	double r = 0.01; //taux d'intérêt
	double sigma = 0.1; //volatilité (constante)
	double T = 2.0; //time to maturity (financement jusqu'à l'échéance)
	int depth = 2;

	VanillaOption* call = new CallOption(K, T);
	VanillaOption* put = new PutOption(K, T);
	/*
	cout << "Call payoff : "<< call->payoff(s)<<"\n"<<endl;
	cout << "Put payoff : " << put->payoff(s) << "\n" << endl;
	
	BlackScholesPricer call_bsp = BlackScholesPricer(call, s, r, sigma);
	BlackScholesPricer put_bsp = BlackScholesPricer(put, s, r, sigma);

	call_bsp.operator()();
	put_bsp.operator()();

	call_bsp.delta();
	put_bsp.delta();*/
	
	/*
	//BinaryTree
	vector<vector<int>> tree;
	BinaryTree<int> test = BinaryTree<int>();
	test.setDepth(3);
	test.setNode(0, 0, 0);
	test.setNode(1, 0, 20);
	test.setNode(1, 1, 0);
	test.setNode(2, 0, 40);
	test.setNode(2, 1, 0);
	test.setNode(2, 2, 80);
	test.setNode(3, 0, 60);
	test.setNode(3, 1, 0);
	test.setNode(3, 2, 100);
	test.setNode(3, 3, 0);
	test.display();
	

	double up = 0.1;
	double down = -0.1;

	CRRPricer pricer = CRRPricer(call, depth, s, up, down, r);
	//cout << pricer.get(0, 0)<<endl;
	pricer.compute();
	*/

    {

        double S0(100.), K(101.), T(5), r(0.01), sigma(0.1);
        CallOption opt1(T, K);
        PutOption opt2(T, K);
        //VanillaOption* opt1 = new CallOption(T,K);
        //VanillaOption* opt2 = new PutOption(T, K);

        cout << "European options 1" << endl << endl;

        {
            //BlackScholesPricer pricer1 = BlackScholesPricer(opt1, S0, r, sigma);
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << endl;

            //BlackScholesPricer pricer2= BlackScholesPricer(opt2, S0, r, sigma);
            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << endl;
            cout << endl;

            int N(5);
            double U = 0.05; //exp(sigma * sqrt(T / N)) - 1.0;
            double D = -0.045; //exp(-sigma * sqrt(T / N)) - 1.0;
            double R = 0.01; //exp(r * T / N) - 1.0;

            //CRRPricer crr_pricer1 = CRRPricer(opt1, N, S0, U, D, R);
            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            cout << "Calling CRR pricer with depth=" << N << endl;
            cout << endl;
            crr_pricer1.compute();
            crr_pricer1.stock_tree.display();
            cout << endl;
            cout << "CRR pricer computed price=" << crr_pricer1() << endl;
            cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << endl;
            cout << endl;

            //CRRPricer crr_pricer2 = CRRPricer(opt2, N, S0, U, D, R);
            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            cout << "Calling CRR pricer with depth=" << N << endl;
            cout << endl;
            crr_pricer2.compute();
            crr_pricer2.stock_tree.display();
            cout << endl;
            cout << "CRR pricer computed price=" << crr_pricer2() << endl;
            cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << endl;
        }
        cout << endl << "*********************************************************" << endl;
    }

    {
        cout << "Binary Tree" << endl << endl;
        BinaryTree<bool> t1;
        t1.setDepth(3);
        t1.setNode(1, 1, true);
        t1.display();
        t1.setDepth(5);
        t1.display();
        t1.setDepth(3);
        t1.display();


        BinaryTree<double> t2;
        t2.setDepth(2);
        t2.setNode(2, 1, 3.140);
        t2.display();
        t2.setDepth(4);
        t2.display();
        t2.setDepth(3);
        t2.display();

        BinaryTree<int> t3;
        t3.setDepth(4);
        t3.setNode(3, 0, 8.000);
        t3.display();
        t3.setDepth(2);
        t3.display();
        t3.setDepth(4);
        t3.display();

        cout << endl << "*********************************************************" << endl;
    }

    {

        double S0(100.), K(101.), T(5.), r(0.01), sigma(0.1);
        DigitalCallOption opt1(T, K);
        DigitalPutOption opt2(T, K);

        cout << "European options 2" << endl << endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << endl;
            cout << endl;

            int N(5);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;

            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            cout << "Calling CRR pricer with depth=" << N << endl;
            cout << endl;
            crr_pricer1.compute();
            crr_pricer1.stock_tree.display();
            cout << endl;
            cout << "CRR pricer computed price=" << crr_pricer1() << endl;
            cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << endl;
            cout << endl;

            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            cout << "Calling CRR pricer with depth=" << N << endl;
            cout << endl;
            crr_pricer2.compute();
            crr_pricer2.stock_tree.display();
            cout << endl;
            cout << "CRR pricer computed price=" << crr_pricer2() <<endl;
            cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << endl;
        }
        cout << endl << "*********************************************************" << endl;


    }
    {
        double S0(100.), K(101.), T(5), r(0.01), sigma(0.1);
        vector<Option*> opt_ptrs;
        opt_ptrs.push_back(new CallOption(T, K));
        opt_ptrs.push_back(new PutOption(T, K));
        opt_ptrs.push_back(new DigitalCallOption(T, K));
        opt_ptrs.push_back(new DigitalPutOption(T, K));

        vector<double> fixing_dates;
        for (int i = 1; i <= 5; i++) {
            fixing_dates.push_back(0.1 * i);
        }
        opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
        opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

        vector<double> ci;
        BlackScholesMCPricer* pricer;

        {
            for (auto& opt_ptr : opt_ptrs) {
                pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
                do {
                    pricer->generate(10);
                    ci = pricer->confidenceInterval();
                } while (ci[1] - ci[0] > 1e-2);
                cout << "nb samples: " << pricer->getNbPaths() << std::endl;
                cout << "price: " << (*pricer)() << std::endl << std::endl;
                delete pricer;
                delete opt_ptr;
            }
            cout << endl << "*********************************************************" << endl;
        }
    }

    {
        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        std::vector<Option*> opt_ptrs;
        opt_ptrs.push_back(new CallOption(T, K));
        opt_ptrs.push_back(new PutOption(T, K));
        opt_ptrs.push_back(new DigitalCallOption(T, K));
        opt_ptrs.push_back(new DigitalPutOption(T, K));
        opt_ptrs.push_back(new AmericanCallOption(T, K));
        opt_ptrs.push_back(new AmericanPutOption(T, K));

        CRRPricer* pricer;

        for (auto& opt_ptr : opt_ptrs) {
            pricer = new CRRPricer(opt_ptr, 150, S0, r, sigma);

            pricer->compute();

            std::cout << "price: " << (*pricer)() << std::endl << std::endl;
            delete pricer;
            delete opt_ptr;

        }
    }
}

