#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdlib>

std::vector< int > lottery_generator(
  std::uniform_int_distribution< int >&,
  std::mt19937&,
  int);

void display_sequence(const std::vector< int >&);

int main (int argc, char** argv)
{
  if ((argc < 5) || (argc > 6))
  {
    std::cout << "Usage:" << std::endl;
    std::cout << "loteca <lower_bound> <upper_bound> <number_quantity> <play_quantity>" << std::endl;
    std::cout << "loteca 1 60 6 10" << std::endl;
    std::cout << std::endl;
    std::cout << "loteca <lower_bound> <upper_bound> <number_quantity> <play_quantity> \"<literal_seed>\"" << std::endl;
    std::cout << "loteca 1 25 15 10 \"01/01/1970 00:00\"" << std::endl;
    std::cout << std::endl;
    return 1;
  }

  std::random_device randomDevice;
  std::mt19937 randomEngine(randomDevice());

  int lowerBound = std::atoi(argv[1]);
  int upperBound = std::atoi(argv[2]);
  int numberQuantity = std::atoi(argv[3]);
  int playQuantity = std::atoi(argv[4]);

  if (argc == 6) {
    std::string userSeed(argv[5]);
    std::seed_seq seed(userSeed.begin(), userSeed.end());

    randomEngine.seed(seed);
  }

  std::uniform_int_distribution< int > distribution(lowerBound, upperBound);

  std::vector< int > sequence;

  for (int i = 1; i <= playQuantity; ++i)
  {
    sequence = lottery_generator(distribution, randomEngine, numberQuantity);

    std::cout << "Game #" << i << std::endl;
    display_sequence(sequence);

    std::vector< int >().swap(sequence);
  }

  return 0;
}

std::vector< int > lottery_generator(
  std::uniform_int_distribution< int >& distribution,
  std::mt19937& engine,
  int quantity)
{
  std::vector< int > sequence;

  for (int i = 0; i < quantity;)
  {
    int numberDrawn = distribution(engine);

    auto it = std::find(sequence.cbegin(), sequence.cend(), numberDrawn);

    if (it != sequence.cend())
    {
      continue;
    }

    sequence.push_back(numberDrawn);
    ++i;
  }

  std::sort(sequence.begin(), sequence.end());

  return sequence;
}

void display_sequence(const std::vector< int >& sequence)
{
  auto it = sequence.cbegin();
  while (it != sequence.cend())
  {
    std::cout << *it << "\t";
    ++it;
  }
  std::cout << std::endl;
}

