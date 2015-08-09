#include <CircleBuf.hpp>

namespace PWRD {

	namespace Utils{

		size_t CircleBuffer::used () {
			if (csp_ < cep_)
				return cep_ - csp_;
			else if (csp_ > cep_)
				return CIRCLE_BUFFSIZE - (csp_ - cep_);

			return full_ ? CIRCLE_BUFFSIZE : 0;
		}
		size_t CircleBuffer::free () {
			return CIRCLE_BUFFSIZE - used();
		}

		/********************
		 * Add from fd to circle buffer
		 * fd: socket
		 * return:
		 ********************/
		ssize_t CircleBuffer::add (ssize_t fd) {

			if (free() == 0)
				return 0;

			ssize_t n=0, n1;
			/* 空闲空间非连续 */
			if (csp_ <= cep_) {
				n = read(fd, cep_, ep_ - cep_);
				if (n <= 0) {
					return n;
				} else if (n < ep_ - cep_) {
					cep_ = cep_ + n;
					return n;
				}
				cep_ = sp_;

			}

			/* 空闲空间连续 */
			if ((n1 = read(fd, cep_, csp_ - cep_)) < 0)
				return n1;

			cep_ = cep_ + n1;

			if (csp_ == cep_)
				full_ = true;

			return n + n1;
		};

		ssize_t CircleBuffer::add (char* src) {
			size_t length = strlen(src);
			return add (src, length);
		};


		/********************
		 * set data from src with length.
		 * return:
		 * 	-201: Not enough memery
		 ********************/
		ssize_t CircleBuffer::add (char* src, size_t length) {

			if (length <= 0)
				return -204;

			if (length > free())
				return -201;

			char *p = src;
			ssize_t n = length;

			/* 空闲空间非连续 */
			if (csp_ <= cep_) {
				if (n <= ep_ - cep_) {
					memcpy (cep_, p, n);
					cep_ = (n == ep_ - cep_) ? sp_ : cep_ + n;

					if (csp_ == cep_)
						full_ = true;

					return length;
				}

				memcpy (cep_, p, ep_ - cep_);
				p = p + (ep_ - cep_);
				n = n - (ep_ - cep_);
				cep_ = sp_;
			}

			/* 空闲空间连续 */
			memcpy (cep_, p, n);
			cep_ = cep_ + n;

			if (csp_ == cep_)
				full_ = true;

			return length;

		};

		/********************
		 * Get data from circle buffer with length.
		 * return:
		 * 	-202: Not enough data 
		 ********************/
		ssize_t CircleBuffer::get (char* dest, size_t length) {

			if (length <= 0)
				return -203;

			if (length > used())
				return -202;

			bzero(dest, length);

			/* 使用空间非连续 */
			ssize_t n1 = length;
			char *p = dest;
			if (csp_ >= cep_) {
				if (n1 <= ep_ - csp_) {
					memcpy(dest, csp_, n1);
					csp_ = (n1 == ep_ - csp_) ? sp_ : csp_ + n1;

					if (csp_ == cep_)
						full_ = false;

					return length;
				}

				memcpy(dest, csp_, ep_ - csp_);
				p = p + (ep_ - csp_);
				n1 = length - (ep_ - csp_);
				csp_ = sp_;
			}

			/* 使用空间连续 */
			memcpy(p, csp_, n1);
			csp_ = csp_ + n1;

			if (csp_ == cep_)
				full_ = false;

			return length;
		}
	}}
