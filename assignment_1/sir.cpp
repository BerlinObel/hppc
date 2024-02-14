#include <iostream>
#include <fstream>
#define beta 0.2
#define gamma 0.1
#define N 1000




void derivative(double S, double I,double& dS, double& dI, double& dR){
	dS = - beta * I * (S / N); 
	dI = beta * I * (S / N) - gamma*I;
	dR = gamma*I;
}

int main(){
	double I = 1;
	double R = 0;
	double S = (N-1);
	double step = 30;
	double t = 0;
	double dS, dI, dR;
	std::ofstream myfile;
  	myfile.open ("sir_output.txt");
  	myfile << "t S I R \n";
	myfile << t << " " << S << " " << I << " " << R << "\n";
	while (t<200.0) {
		t = t + step;
		derivative(S,I,dS,dI,dR);
		S += step*dS;
		I += step*dI;
		R += step*dR;
		myfile << t << " " << S << " " << I << " " << R << "\n";
	}
	myfile.close();
	
return 0;}

