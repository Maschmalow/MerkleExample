#pragma once
/** \file
 * \brief Crypto related operations
 */

#include <cryptlib.h>
#include <sha.h>

#include <array>
#include <ranges>
#include <optional>




/**
 *  Project namespace
 */
namespace merkle {

    /** \class merkle::Hash
     * \brief byte array containing a hash digest.
     */
    using Hash = std::array<CryptoPP::byte, CryptoPP::SHA256::DIGESTSIZE>;


    class Hasher;

    /**\interface   directlyHashable
     * \brief Concept modelling types that can be hashed as is, using sifzeof.
     * \details `directlyHashable = std::is_arithmetic_v<T>;`
     */
    template<class T>
    concept directlyHashable = std::is_arithmetic_v<T>;

    /**\interface   contiguous_hashable
     * \brief Concept modelling continuous arrays of directly hashable elements, ie, types that can be hashed with a single call.
     */
    template<class T>
    concept contiguous_hashable = std::ranges::contiguous_range<T> &&
                                  std::ranges::sized_range<T> && directlyHashable<std::ranges::range_value_t<T>>;


    /**\interface iterable
     * \brief Concept modelling types that supports Range-based for loop.
     */
    template<class T>
    concept iterable = requires(T &in) {
        std::begin(in) != std::end(in);
        ++std::begin(in);
        *std::begin(in);
    };



    /**\interface implementsAddToHash
     * \brief Concept modelling types implementing addToHash().
     */
    template<class T>
    concept implementsAddToHash = requires(const T x, Hasher &in) {
        {x.addToHash(in)} -> std::same_as<void>;
    };

    /**
     * \brief Inherit this class and implement addToHash() to define hashing of a custom class.
     * \details To use it on your class, inherit Hashable and implement "void addToHash(Hasher &in) const".
     */
    class Hashable {  };

    /**\interface derived_hashable
     * \brief Concept modelling types supporting hashing though addToHash().
     * \details We do not use the implementsAddToHash directly because we would risk
     * having external classes inadvertently implementing addToHash in unexpected ways.
     * Other implementations are possible with different trade-offs, eg, CRTP, type tag, virtual class, etc.
     */
    template<class T>
    concept derived_hashable = std::derived_from<T, Hashable> && implementsAddToHash<T>;


    /**
     * \brief SHA256 instance.
     * \details A Hasher instance holds the state of the hash function. Use input() to feed data to the hash function and end() to get the hash.
     * The hash can also be directly computed using the static member apply().
     */
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


        /**
         * Arithmetic type are \ref directlyHashable  using the sizeof() operator.
         */
        template<directlyHashable T>
        Hasher &input(const T &in) {
            return inputRaw(&in, sizeof(in));
        }

        /**
         * The hashing of a contiguous array of directlyHashable elements (\ref contiguous_hashable) is done in a single call to the underlying hash function.
         */
        template<contiguous_hashable T>
        Hasher &input(const T &in) {
            return inputRaw(std::data(in), std::size(in) * sizeof(*std::data(in)));
        }

        /**
         * Anything \ref iterable (excluding contiguous arrays of directlyHashable elements) is hashed element by element.
         */
        template<iterable T>
        requires (!contiguous_hashable<T>)
        Hasher &input(const T &in) {
            for (const auto &cur: in)
                this->input(cur);

            return *this;
        }


        /**
         * A \ref derived_hashable instance calls its addToHash() member function.
         */
        template<derived_hashable T>
        Hasher &input(const T &in) {
            in.addToHash(*this);
            return *this;
        }


        /**
         * Static function to hash values in one call. Generates one call to the underlying hash function per input argument.
         */
        template<class... TArgs>
        static Hash apply(const TArgs &...ins) {
            Hasher h{};
            (h.input(ins), ...);
            return h.end();
        }


        /**
         * End the hash inputs and return the hash value.
         */
        Hash end() {
            Hash ret;
            hasher.Final(ret.data());
            return ret;
        }

    };


}