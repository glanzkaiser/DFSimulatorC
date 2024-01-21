// g++ -o result main.cpp 

#include <iostream>
#include <bits/stdc++.h>
#define n 3
 
//using namespace std;
 
void svd(std::vector<std::vector<arg>> matrix, std::vector<std::vector<arg>>& s,
	std::vector<std::vector<arg>>& u, std::vector<std::vector<arg>>& v)
{
	std::vector<std::vector<arg>> matrix_t;
	matrix_transpose(matrix, matrix_t);

	std::vector<std::vector<arg>> matrix_product1;
	matrix_by_matrix(matrix, matrix_t, matrix_product1);

	std::vector<std::vector<arg>> matrix_product2;
	matrix_by_matrix(matrix_t, matrix, matrix_product2);

	std::vector<std::vector<arg>> u_1;
	std::vector<std::vector<arg>> v_1;

	std::vector<arg> eigenvalues;
	compute_evd(matrix_product2, eigenvalues, v_1, 0);

	matrix_transpose(v_1, v);

	s.resize(matrix.size());
	for (std::uint32_t index = 0; index < eigenvalues.size(); index++)
	{
		s[index].resize(eigenvalues.size());
		s[index][index] = eigenvalues[index];
	}

	std::vector<std::vector<arg>> s_inverse;
	get_inverse_diagonal_matrix(s, s_inverse);

	std::vector<std::vector<arg>> av_matrix;
	matrix_by_matrix(matrix, v, av_matrix);
	matrix_by_matrix(av_matrix, s_inverse, u);
}

// This function performs the computation of eigenvalues and eigenvectors of a given factorization matrix:
void compute_evd(std::vector<std::vector<arg>> matrix,
	std::vector<arg>& eigenvalues, std::vector<std::vector<arg>>& eigenvectors, 
                      std::size_t eig_count)
{
	std::size_t m_size = matrix.size();
	std::vector<arg> vec; vec.resize(m_size);
	std::fill_n(vec.begin(), m_size, 1);

	static std::vector<std::vector<arg>> matrix_i;

	if (eigenvalues.size() == 0 && eigenvectors.size() == 0)
	{
		eigenvalues.resize(m_size);
		eigenvectors.resize(eigenvalues.size());
		matrix_i = matrix;
	}

	std::vector<std::vector<arg>> m; m.resize(m_size);
	for (std::uint32_t row = 0; row < m_size; row++)
		m[row].resize(100);

	Arg lambda_old = 0;

	std::uint32_t index = 0; bool is_eval = false;
	while (is_eval == false)
	{
		for (std::uint32_t row = 0; row < m_size && (index % 100) == 0; row++)
			m[row].resize(m[row].size() + 100);

		for (std::uint32_t row = 0; row < m_size; row++)
		{
			m[row][index] = 0;
			for (std::uint32_t col = 0; col < m_size; col++)
				m[row][index] += matrix[row][col] * vec[col];
		}

		for (std::uint32_t col = 0; col < m_size; col++)
			vec[col] = m[col][index];

		if (index > 0)
		{
			Arg lambda = (m[0][index - 1] != 0) ? \
				(m[0][index] / m[0][index - 1]) : m[0][index];
			is_eval = (std::fabs(lambda - lambda_old) < 0.0000000001) ? true : false;

			lambda = (std::fabs(lambda) >= 10e-6) ? lambda : 0;
			eigenvalues[eig_count] = lambda; lambda_old = lambda;
		}

		index++;
	}

	std::vector<std::vector<arg>> matrix_new;

	if (m_size > 1)
	{
		std::vector<std::vector<arg>> matrix_target;
		matrix_target.resize(m_size);

		for (std::uint32_t row = 0; row < m_size; row++)
		{
			matrix_target[row].resize(m_size);
			for (std::uint32_t col = 0; col < m_size; col++)
				matrix_target[row][col] = (row == col) ? \
				(matrix[row][col] - eigenvalues[eig_count]) : matrix[row][col];
		}

		std::vector<arg> eigenvector;
		jordan_gaussian_transform(matrix_target, eigenvector);

		std::vector<std::vector<arg>> hermitian_matrix;
		get_hermitian_matrix(eigenvector, hermitian_matrix);

		std::vector<std::vector<arg>> ha_matrix_product;
		matrix_by_matrix(hermitian_matrix, matrix, ha_matrix_product);

		std::vector<std::vector<arg>> inverse_hermitian_matrix;
		get_hermitian_matrix_inverse(eigenvector, inverse_hermitian_matrix);

		std::vector<std::vector<arg>> iha_matrix_product;
		matrix_by_matrix(ha_matrix_product, 
                         inverse_hermitian_matrix, iha_matrix_product);

		get_reduced_matrix(iha_matrix_product, matrix_new, m_size - 1);
	}

	if (m_size <= 1)
	{
		for (std::uint32_t index = 0; index < eigenvalues.size(); index++)
		{
			Arg lambda = eigenvalues[index];
			std::vector<std::vector<arg>> matrix_target;
			matrix_target.resize(matrix_i.size());

			for (std::uint32_t row = 0; row < matrix_i.size(); row++)
			{
				matrix_target[row].resize(matrix_i.size());
				for (std::uint32_t col = 0; col < matrix_i.size(); col++)
					matrix_target[row][col] = (row == col) ? \
					(matrix_i[row][col] - lambda) : matrix_i[row][col];
			}

			eigenvectors.resize(matrix_i.size());
			jordan_gaussian_transform(matrix_target, eigenvectors[index]);

			Arg eigsum_sq = 0;
			for (std::uint32_t v = 0; v < eigenvectors[index].size(); v++)
				eigsum_sq += std::pow(eigenvectors[index][v], 2.0);

			for (std::uint32_t v = 0; v < eigenvectors[index].size(); v++)
				eigenvectors[index][v] /= sqrt(eigsum_sq);

			eigenvalues[index] = std::sqrt(eigenvalues[index]);
		}

		return;
	}

	compute_evd(matrix_new, eigenvalues, eigenvectors, eig_count + 1);

	return;
}

// These two functions allow us to find Hermitian matrix and its inverse:

void get_hermitian_matrix(std::vector<arg> eigenvector,
	std::vector<std::vector<arg>>& h_matrix)
{
	h_matrix.resize(eigenvector.size());
	for (std::uint32_t row = 0; row < eigenvector.size(); row++)
		h_matrix[row].resize(eigenvector.size());

	h_matrix[0][0] = 1 / eigenvector[0];
	for (std::uint32_t row = 1; row < eigenvector.size(); row++)
		h_matrix[row][0] = -eigenvector[row] / eigenvector[0];

	for (std::uint32_t row = 1; row < eigenvector.size(); row++)
		h_matrix[row][row] = 1;
}

void get_hermitian_matrix_inverse(std::vector<arg> eigenvector,
	std::vector<std::vector<arg>>& ih_matrix)
{
	ih_matrix.resize(eigenvector.size());
	for (std::uint32_t row = 0; row < eigenvector.size(); row++)
		ih_matrix[row].resize(eigenvector.size());

	ih_matrix[0][0] = eigenvector[0];
	for (std::uint32_t row = 1; row < eigenvector.size(); row++)
		ih_matrix[row][0] = -eigenvector[row];

	for (std::uint32_t row = 1; row < eigenvector.size(); row++)
		ih_matrix[row][row] = 1;
}

// The following function performs Jordan-Gaussian transformation of a given factorization matrix:

void jordan_gaussian_transform(
	std::vector<std::vector<arg>> matrix, std::vector<arg>& eigenvector)
{
	const Arg eps = 0.000001; bool eigenv_found = false;
	for (std::uint32_t s = 0; s < matrix.size() - 1 && !eigenv_found; s++)
	{
		std::uint32_t col = s; Arg alpha = matrix[s][s];
		while (col < matrix[s].size() && alpha != 0 && alpha != 1)
			matrix[s][col++] /= alpha;

		for (std::uint32_t col = s; col < matrix[s].size() && !alpha; col++)
			std::swap(matrix[s][col], matrix[s + 1][col]);

		for (std::uint32_t row = 0; row < matrix.size(); row++)
		{
			Arg gamma = matrix[row][s];
			for (std::uint32_t col = s; col < matrix[row].size() && row != s; col++)
				matrix[row][col] = matrix[row][col] - matrix[s][col] * gamma;
		}

		std::uint32_t row = 0;
		while (row < matrix.size() &&
			(s == matrix.size() - 1 || std::fabs(matrix[s + 1][s + 1]) < eps))
			eigenvector.push_back(-matrix[row++][s + 1]);

		if (eigenvector.size() == matrix.size())
		{
			eigenv_found = true; eigenvector[s + 1] = 1;
			for (std::uint32_t index = s + 1; index < eigenvector.size(); index++)
				eigenvector[index] = (std::fabs(eigenvector[index]) >= eps) ? 
                eigenvector[index] : 0;
		}
	}
} 

// The following function is used to find an inverse diagonal matrix S:
void get_inverse_diagonal_matrix(std::vector<std::vector<arg>> matrix,
	std::vector<std::vector<arg>>& inv_matrix)
{
	inv_matrix.resize(matrix.size());
	for (std::uint32_t index = 0; index < matrix.size(); index++)
	{
		inv_matrix[index].resize(matrix[index].size());
		inv_matrix[index][index] = 1.0 / matrix[index][index];
	}
}

// This function allows us to compute an equivalent matrix B:

void get_reduced_matrix(std::vector<std::vector<arg>> matrix,
	std::vector<std::vector<arg>>& r_matrix, std::size_t new_size)
{
	r_matrix.resize(new_size);
	std::size_t index_d = matrix.size() - new_size;
	std::uint32_t row = index_d, row_n = 0;
	while (row < matrix.size())
	{
		r_matrix[row_n].resize(new_size);
		std::uint32_t col = index_d, col_n = 0;
		while (col < matrix.size())
			r_matrix[row_n][col_n++] = matrix[row][col++];

		row++; row_n++;
	}
} 

// The following trivial function performs multiplication of two matrices:
void matrix_by_matrix(std::vector<std::vector<arg>> matrix1,
	std::vector<std::vector<arg>>& matrix2, std::vector<std::vector<arg>>& matrix3)
{
	matrix3.resize(matrix1.size());
	for (std::uint32_t row = 0; row < matrix1.size(); row++)
	{
		matrix3[row].resize(matrix1[row].size());
		for (std::uint32_t col = 0; col < matrix1[row].size(); col++)
		{
			matrix3[row][col] = 0.00;
			for (std::uint32_t k = 0; k < matrix1[row].size(); k++)
				matrix3[row][col] += matrix1[row][k] * matrix2[k][col];
		}
	}
}

// The following trivial function allows us to find a transpose of a given matrix:
void matrix_transpose(std::vector<std::vector<arg>> matrix1,
	std::vector<std::vector<arg>>& matrix2)
{
	matrix2.resize(matrix1.size());
	for (std::uint32_t row = 0; row < matrix1.size(); row++)
	{
		matrix2[row].resize(matrix1[row].size());
		for (std::uint32_t col = 0; col < matrix1[row].size(); col++)
			matrix2[row][col] = matrix1[col][row];
	}
}
    
// These two functions allow us to generate and print out matrices:

void generate_matrix(std::vector<std::vector<long double="">>& \
	matrix, std::size_t rows, std::size_t cols)
{
	std::srand((unsigned int)std::time(nullptr)); matrix.resize(rows);
	for (std::size_t row = 0; row < matrix.size(); row++)
	{
		matrix[row].resize(cols);
		for (std::size_t col = 0; col < matrix[row].size(); col++)
			matrix[row][col] = std::rand() % 20 - std::rand() % 20;
	}
}

void print_matrix(std::vector<std::vector<long double="">>	matrix)
{
	for (std::size_t row = 0; row < matrix.size(); row++)
	{
		for (std::size_t col = 0; col < matrix[row].size(); col++)
			std::cout << std::setprecision(5) << std::fixed << matrix[row][col] << " ";

		std::cout << "\n";
	}

	std::cout << "\n";
} 

int main(int argc, char* argv[])
{
	std::size_t matrix_size = 0;
	std::vector<std::vector<long double="">> u, v;
	std::vector<std::vector<long double="">> matrix, s;
	std::cout << "Singular Value Decomposition (SVD):\n\n";
	
	std::cout << "Enter size of matrix N = "; std::cin >> matrix_size;
	
	generate_matrix(matrix, matrix_size, matrix_size); 
	
	std::cout << "\nA = \n"; print_matrix(matrix);

	svd(matrix, s, u, v);

	std::cout << "\nS = \n"; print_matrix(s);
	std::cout << "\nU = \n"; print_matrix(u);
	std::cout << "\nV = \n"; print_matrix(v);

	std::cin.get();
	std::cin.get();

	return 0;
}