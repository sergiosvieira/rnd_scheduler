#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
using VectorOfDouble = std::vector<double>;

VectorOfDouble gen(unsigned int size, unsigned int max)
{
	VectorOfDouble result(size);
	random_device rnd_dev;
	mt19937 mt_engine(rnd_dev());
	uniform_real_distribution<double> urd(0, max);
	auto g = std::bind(urd, mt_engine);
	generate(begin(result), end(result), g);
	return result;
}

double rnd_initial(unsigned int max)
{
	random_device r_dev;
	mt19937 mt_engine(r_dev());
	uniform_real_distribution<double> urd(1, max);
	return urd(mt_engine);
}

void print(VectorOfDouble v)
{
	std::cout << "[";
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i];
		if (i < v.size() - 1) std::cout << ", ";
	}
	std::cout << "]"; 
}

double sum(VectorOfDouble v)
{
	double total = 0.;
	for (auto& d : v) total += d;
	return total;
}

int main(int argc, char** argv)
{
	int total_consumers = 10;
	double total = rnd_initial(10000000000000);
	double consumed = 0.0;
	VectorOfDouble value = gen(total_consumers, 1);
	VectorOfDouble consumed_values(total_consumers);
	double available = 0.0;
	int i = 0;
	do
	{
		available = total - consumed;
		if (available > 0)
		{
			unsigned int index = i % value.size();
			if (value[index] < available)
			{
				consumed += value[index];
				consumed_values[index] += value[index];
				++i;
			}
			else 
			{
				consumed += available;
				consumed_values[index] += available;
				break;
			}
		}
	} while (available > 0.0);
	std::cout << "\nTotal = " << total << "\n";
	std::cout << "Consumed = " << consumed << "\n";
	std::cout << "Consumers Sum  = " << sum(consumed_values) << "\n";
}
