#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <fstream>

bool isInCircles(double x, double y, double x1, double y1, double r1, double x2,
                 double y2, double r2, double x3, double y3, double r3) {
  return (x - x1) * (x - x1) + (y - y1) * (y - y1) <= r1 * r1 &&
         (x - x2) * (x - x2) + (y - y2) * (y - y2) <= r2 * r2 &&
         (x - x3) * (x - x3) + (y - y3) * (y - y3) <= r3 * r3;
}

double monteCarloIntersection_BigRectangleArea(double x1, double y1, double r1, double x2,
                              double y2, double r2, double x3, double y3,
                              double r3, long points_amount) {

  // Границы прямоугольника, в котором лежат все три окружности точно
  // (способ 1)
  double x_min = std::min({x1 - r1, x2 - r2, x3 - r3});
  double x_max = std::max({x1 + r1, x2 + r2, x3 + r3});
  double y_min = std::min({y1 - r1, y2 - r2, y3 - r3});
  double y_max = std::max({y1 + r1, y2 + r2, y3 + r3});

  // Основные настройки для генератора
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis_X(x_min, x_max);
  std::uniform_real_distribution<> dis_Y(y_min, y_max);

  // Как написано в задании, M - количество попадающих точек, 
  // N = points_amount - кол-во всех точек
  int M_cnt = 0;
  for (int i = 0; i < points_amount; ++i) {
    double x = dis_X(gen);
    double y = dis_Y(gen);

    if (isInCircles(x, y, x1, y1, r1, x2, y2, r2, x3, y3, r3)) {
      ++M_cnt;
    }
  }

  double rect_area = (x_max - x_min) * (y_max - y_min);

  return (static_cast<double>(M_cnt) / points_amount) * rect_area;
}

double monteCarloIntersection_SmallerRectangleArea(double x1, double y1, double r1,
                                               double x2, double y2, double r2,
                                               double x3, double y3, double r3,
                                               long points_amount) {

  // Границы прямоугольника, который заключает в себе преимущественно только площадь необходимую нам
  // (способ 2)
  double x_min = 0.85;
  double x_max = 2.1;
  double y_min = 0.85;
  double y_max = 2.1;

  // Основные настройки для генератора
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis_X(x_min, x_max);
  std::uniform_real_distribution<> dis_Y(y_min, y_max);

  // Как написано в задании, M - количество попадающих точек,
  // N = points_amount - кол-во всех точек
  int M_cnt = 0;
  for (int i = 0; i < points_amount; ++i) {
    double x = dis_X(gen);
    double y = dis_Y(gen);

    if (isInCircles(x, y, x1, y1, r1, x2, y2, r2, x3, y3, r3)) {
      ++M_cnt;
    }
  }

  double rect_area = (x_max - x_min) * (y_max - y_min);

  return (static_cast<double>(M_cnt) / points_amount) * rect_area;
}

int main() {
  
  double x1 = 1.0, y1 = 1.0, r1 = 1.0;
  double x2 = 1.5, y2 = 2.0, r2 = (std::sqrt(5)/2.0);
  double x3 = 2.0, y3 = 1.5, r3 = (std::sqrt(5) / 2.0);

  // Точное значение площади
  double exactArea = 0.944516185899465;

  std::vector<long> points_list;
  std::vector<double> areas1;
  std::vector<double> deviations1;
  std::vector<double> areas2;
  std::vector<double> deviations2;

  for (long points = 100; points <= 100000; points += 500) {

    double result_area1 = monteCarloIntersection_BigRectangleArea(
        x1, y1, r1, x2, y2, r2, x3, y3, r3, points);
    double deviation1 = std::abs((result_area1 - exactArea) / exactArea) * 100;

    double result_area2 = monteCarloIntersection_SmallerRectangleArea(
        x1, y1, r1, x2, y2, r2, x3, y3, r3, points);
    double deviation2 = std::abs((result_area2 - exactArea) / exactArea) * 100;

    points_list.push_back(points);
    areas1.push_back(result_area1);
    deviations1.push_back(deviation1);
    areas2.push_back(result_area2);
    deviations2.push_back(deviation2);
  }

  std::ofstream outputFile("data.txt");

  outputFile << "Points; Area_method1; Deviation_method1 (%); Area_method2; Deviation_method2(%); \n";

  for (size_t i = 0; i < points_list.size(); ++i) {
    outputFile << points_list[i] << "; " << areas1[i] << "; " << deviations1[i]
               << "; " << areas2[i] << "; " << deviations2[i]
               << "\n";
  }

  return 0;
}
