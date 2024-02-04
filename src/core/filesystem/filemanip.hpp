#pragma once
// #define _CRT_SECURE_NO_WARNINGS       // fopen vs fopen_s
#include <cstdio>      // fopen, fclose, fseek, ftell, fread, fwrite
#include <memory>      // std::unique_ptr
#include <string_view> // std::string_view

#include <fstream>

#include <rsl/primitives> // rsl::byte, rsl::byte_vec
#include <rsl/type_util>  // [[nodiscard]]
#include <rsl/utilities>  // rsl_assert_msg



namespace rythe::core::filesystem
{


	/**@brief Check if file exists.
	 * @param [in] path The path of the file to check.
	 */
	[[nodiscard]] inline bool exists(std::string_view path)
	{
		FILE* f = fopen(std::string(path).c_str(), "r+b");

		if (f)
		{
			fclose(f);
			return true;
		}
		return false;
	}

	/**@brief Open File in binary mode and write to buffer.
	 *
	 * @param [in] path The path of the file to open.
	 * @return A vector of bytes with the contents of the file at path.
	 */
	[[nodiscard]] inline rsl::byte_vec read_file(std::string_view path)
	{
		std::ifstream file(path.data(), std::ios::ate | std::ios::binary);

		rsl_assert_msg("could not open file", file.is_open());

		size_t fileSize = (size_t)file.tellg();
		rsl::byte_vec buffer(fileSize);

		file.seekg(0);
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

		file.close();

		return buffer;
	}

	/**@brief Open file in binary mode to write the buffer to it.
	 *
	 * @param [in] path The path of the file you want to write to.
	 * @param [in] container The buffer you want to write to the file.
	 */
	inline void write_file(std::string_view path, const rsl::byte_vec& container)
	{

		// create managed FILE ptr
		const std::unique_ptr<FILE, decltype(&fclose)> file(
			fopen(std::string(path).c_str(), "wb"),
			fclose
		);

		rsl_assert_msg("could not open file", file);

		// read data
		fwrite(container.data(), sizeof(rsl::byte), container.size(), file.get());
	}


	/**@brief Work the same as the above, but the path
	 *  parameter is replaced by the string literal.
	 */
	namespace literals
	{
		rsl::byte_vec RYTHE_FUNC operator""_readfile(const char* str, std::size_t len);

		auto RYTHE_FUNC operator""_writefile(const char* str, std::size_t len);

		bool RYTHE_FUNC operator""_exists(const char* str, std::size_t len);
	} // namespace literals
} // namespace rythe::core::filesystem

#undef _CRT_SECURE_NO_WARNINGS

// code example
/*
void example()
{
	using namespace  rythe::core::fs::literals;

	auto file1 = "hello_world.cpp"_readfile;
	auto file2 = rythe::core::fs::read_file("hello_world.cpp");

	"hello_world2.cpp"_writefile(file2);
	rythe::core::fs::write_file("hello_world2.cpp",file1);
}
*/
