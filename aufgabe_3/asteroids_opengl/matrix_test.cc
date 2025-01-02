#include "matrix.h"
#include "gtest/gtest.h"

namespace {
  TEST(MATRIX, ListInitialization2df) {
    SquareMatrix2df matrix = { Vector2df{1.0, 0.0},
                               Vector2df{0.0, 1.0} };

    EXPECT_NEAR(1.0, matrix.at(0,0), 0.00001);
    EXPECT_NEAR(0.0, matrix.at(0,1), 0.00001);
    EXPECT_NEAR(0.0, matrix.at(1,0), 0.00001);
    EXPECT_NEAR(1.0, matrix.at(1,1), 0.00001);
  }

  TEST(MATRIX, ListInitialization3df) {
    SquareMatrix3df matrix = { Vector3df{1.0, 0.0, 0.0},
                               Vector3df{0.0, 1.0, 0.0},
                               Vector3df{0.0, 0.0, 1.0} };

    EXPECT_NEAR(1.0, matrix[0][0], 0.00001);
    EXPECT_NEAR(0.0, matrix[0][1], 0.00001);
    EXPECT_NEAR(0.0, matrix[0][2], 0.00001);
    EXPECT_NEAR(0.0, matrix[1][0], 0.00001);
    EXPECT_NEAR(1.0, matrix[1][1], 0.00001);
    EXPECT_NEAR(0.0, matrix[1][2], 0.00001);
    EXPECT_NEAR(0.0, matrix[2][0], 0.00001);
    EXPECT_NEAR(0.0, matrix[2][1], 0.00001);
    EXPECT_NEAR(1.0, matrix[2][2], 0.00001);
  }

  TEST(MATRIX, ListInitialization4df) {
    SquareMatrix4df matrix = { {1.0, 5.0, 9.0, 13.0},
                               {2.0, 6.0, 10.0, 14.0},
                               {3.0, 7.0, 11.0, 15.0},
                               {4.0, 8.0, 12.0, 16.0} };

    float v = 1.0f;
    for (size_t row = 0; row < 4; row++) {
      for (size_t column = 0;  column < 4; column++) {
        EXPECT_NEAR(v++, matrix.at(row, column), 0.00001);
      }
    }
  }



  TEST(MATRIX, ProductWithVector3df) {
    SquareMatrix3df matrix = { {1.0, 0.0, 1.0},
                               {0.0, 1.0, 1.0},
                               {0.0, 0.0, 1.0} };
    Vector3df vector = {-6.0, 3.0,  1.0};
    Vector3df product = matrix * vector;

    EXPECT_NEAR(-6.0, product[0], 0.00001);
    EXPECT_NEAR( 3.0, product[1], 0.00001);
    EXPECT_NEAR(-2.0, product[2], 0.00001);
  }



  TEST(MATRIX, ProductWithMatrix2df) {
    SquareMatrix2df matrix1 = { {1.0, 2.0},
                                {-1.0, 1.5} };
    SquareMatrix2df matrix2 = { {2.0, -1.0},
                                {1.0, 0.0} };
    SquareMatrix2df matrix = matrix1 * matrix2;

    EXPECT_NEAR( 3.0, matrix.at(0,0), 0.00001);
    EXPECT_NEAR( 1.0, matrix.at(0,1), 0.00001);
    EXPECT_NEAR( 2.5, matrix.at(1,0), 0.00001);
    EXPECT_NEAR( 2.0, matrix.at(1,1), 0.00001);
  }

  // Aufgabe_3 - Tests

  TEST(MATRIX, EmptyListInitialization) {
    SquareMatrix3df matrix = SquareMatrix3df();
    EXPECT_NEAR(0.0, matrix.at(0,0), 0.00001);
    EXPECT_NEAR(0.0, matrix.at(1,0), 0.00001);
    EXPECT_NEAR(0.0, matrix.at(0,1), 0.00001);
    EXPECT_NEAR(0.0, matrix.at(1,1), 0.00001);
  }

  TEST(MATRIX, AtFunction) {
    SquareMatrix3df matrix = { {1.0, 2.0},
                                {-1.0, 1.5} };

    EXPECT_NEAR(1.0, matrix.at(0,0), 0.00001);
    EXPECT_NEAR(2.0, matrix.at(1,0), 0.00001);
    EXPECT_NEAR(-1.0, matrix.at(0,1), 0.00001);
    EXPECT_NEAR(1.5, matrix.at(1,1), 0.00001);
  }

  TEST(MATRIX, ProductMultiplicationWithMatrix2df) {
    // Define two 2x2 matrices
    SquareMatrix2df matrix1 = { {1.0f, 2.0f}, {3.0f, 4.0f} };
    SquareMatrix2df matrix2 = { {5.0f, 6.0f}, {7.0f, 8.0f} };

    // Expected result of matrix1 * matrix2
    SquareMatrix2df expected = { {23.0f, 34.0f}, {31.0f, 46.0f} };

    // Perform multiplication
    SquareMatrix2df result = matrix1 * matrix2;

    // Check if the result matches the expected result
    for (size_t c = 0; c < 2; ++c) {
      for (size_t r = 0; r < 2; ++r) {
        EXPECT_FLOAT_EQ(result.at(r, c), expected.at(r, c));
      }
    }
  }

  TEST(MATRIX, ProductMultiplicationWithMatrix3df) {
    // Define two 2x2 matrices
    SquareMatrix3df matrix1 = { {1.0f, 2.0f, -2.0f}, {3.0f, 4.0f, 5.0f}, {0.0f, -2.0f, -1.0f} };
    SquareMatrix3df matrix2 = { {5.0f, 6.0f, 1.0f}, {7.0f, 8.0f, -3.0f}, {4.0f, 2.0f, 3.0f} };

    // Expected result of matrix1 * matrix2
    SquareMatrix3df expected = { {23.0f, 32.0f, 19.0f}, {31.0f, 52.0f, 29.0f}, {10, 10, -1} };

    // Perform multiplication
    SquareMatrix3df result = matrix1 * matrix2;

    // Check if the result matches the expected result
    for (size_t c = 0; c < 2; ++c) {
      for (size_t r = 0; r < 2; ++r) {
        EXPECT_FLOAT_EQ(result.at(r, c), expected.at(r, c));
      }
    }
  }
  // ProductWithVector defined above
}
