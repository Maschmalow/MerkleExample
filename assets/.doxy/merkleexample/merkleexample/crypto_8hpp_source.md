

# File crypto.hpp

[**File List**](files.md) **>** [**include**](dir_e5730d5bb186076c7325630a058c9a00.md) **>** [**merklelib**](dir_5209bc8e00a5022dcb375bc5a32c3450.md) **>** [**crypto.hpp**](crypto_8hpp.md)

[Go to the documentation of this file](crypto_8hpp.md)

```C++

#pragma once
#include <cryptlib.h>
#include <sha.h>

#include <array>
#include <ranges>
#include <optional>




namespace merkle {

    using Hash = std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>;


    class Hasher;

    template<class T>
    concept directlyHashable = std::is_arithmetic_v<T>;

    template<class T>
    concept contiguous_hashable = std::ranges::contiguous_range<T> &&
                                  std::ranges::sized_range<T> && directlyHashable<std::ranges::range_value_t<T>>;


    template<class T>
    concept iterable = requires(T &in) {
        std::begin(in) != std::end(in);
        ++std::begin(in);
        *std::begin(in);
    };



    template<class T>
    concept implementsAddToHash = requires(const T x, Hasher &in) {
        {x.addToHash(in)} -> std::same_as<void>;
    };

    class Hashable {  };

    template<class T>
    concept derived_hashable = std::derived_from<T, Hashable> && implementsAddToHash<T>;


    class Hasher {
    private:
        CryptoPP::SHA256 hasher;

        template<class T>
        Hasher &inputRaw(const T *ptr, std::size_t n) {
            hasher.Update(reinterpret_cast<const CryptoPP::byte *>(ptr), n);
            return *this;
        }

    public:
        Hasher() = default;


        template<directlyHashable T>
        Hasher &input(const T &in) {
            return inputRaw(&in, sizeof(in));
        }

        template<contiguous_hashable T>
        Hasher &input(const T &in) {
            return inputRaw(std::data(in), std::size(in) * sizeof(*std::data(in)));
        }

        template<iterable T>
        requires (!contiguous_hashable<T>)
        Hasher &input(const T &in) {
            for (const auto &cur: in)
                this->input(cur);

            return *this;
        }


        template<derived_hashable T>
        Hasher &input(const T &in) {
            in.addToHash(*this);
            return *this;
        }


        template<class... TArgs>
        static Hash apply(const TArgs &...ins) {
            Hasher h{};
            (h.input(ins), ...);
            return h.end();
        }


        Hash end() {
            Hash ret;
            hasher.Final(ret.data());
            return ret;
        }

    };


}

```

