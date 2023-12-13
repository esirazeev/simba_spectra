#ifndef PCAP_RAW_BUFFER_HPP
#define PCAP_RAW_BUFFER_HPP

#include <cstdint>
#include <fstream>

namespace pcap
{
class RawBuffer final
{
public:
	RawBuffer() noexcept;
	RawBuffer(const RawBuffer&);
	RawBuffer(RawBuffer&&);
	RawBuffer& operator=(const RawBuffer&);
	RawBuffer& operator=(RawBuffer&&);
	~RawBuffer();

	/**
	 * @brief Reallocates the buffer. All current data will be lost.
	 * 
	 * @param size New buffer size
	 */
	void reallocate(uint32_t size);

	/**
	 * @brief Fills a buffer.
	 * 
	 * @param data Raw data
	 * @param size Raw data size
	 */
	void fill(const uint8_t* data, uint32_t size);

	/**
	 * @brief Fills a buffer from a file.
	 * 
	 * @param file File object
	 * @param size Read byte size
	 * 
	 * @return Number of bytes that were filled
	 */
	void fill(std::ifstream& file, uint32_t size);

	/**
	 * @brief Returns raw data.
	 * 
	 * @return Raw data
	 */
	const uint8_t* data() const noexcept;

	/**
	 * @brief Returns raw data size.
	 * 
	 * @return Raw data size
	 */
	const uint32_t size() const noexcept;

private:
	void allocate(uint32_t size);
	void copy(const uint8_t* buffer, uint32_t size);
	void destroy();

	uint8_t* buffer_;
	uint32_t dataSize_;
	uint32_t bufferSize_;
};

} // namespace pcap

#endif // PCAP_RAW_BUFFER_HPP
