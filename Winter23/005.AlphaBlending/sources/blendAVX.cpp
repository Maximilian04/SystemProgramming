#include "include.h"
#include "getPrName.cpp"
#include "coord2index.cpp"

const char WINNAME[] = "alphaBlendingAVX";
const int32_t BOOST_F = 8;

static const size_t HALF256_OFFSET = 16; // (sizeof(__m256i) >> 1)

#define LINESEQ(n) n, n, n, -0x80

alignas(32) const __m256i ALPHASEQ = _mm256_setr_epi8(
    LINESEQ(0x03),
    LINESEQ(0x07),
    LINESEQ(0x0B),
    LINESEQ(0x0F),
    LINESEQ(0x03),
    LINESEQ(0x07),
    LINESEQ(0x0B),
    LINESEQ(0x0F));
//  index, index, index, 0b10000000
#undef LINESEQ

#define LINESEQ -1, -1, -1, 0

alignas(32) const __m256i ALPHA255SEQ = _mm256_setr_epi8(
    LINESEQ,
    LINESEQ,
    LINESEQ,
    LINESEQ,
    LINESEQ,
    LINESEQ,
    LINESEQ,
    LINESEQ);
//  255 255 255 0
#undef LINESEQ

#define LINESEQ -0x80, -0x80, -0x80, -0x80

alignas(32) const __m256i PACK_LO_SEQ = _mm256_setr_epi8(
    0x01, 0x03, 0x05, -0x80,
    0x09, 0x0B, 0x0D, -0x80,
    LINESEQ,
    LINESEQ,
    0x11, 0x13, 0x15, -0x80,
    0x19, 0x1B, 0x1D, -0x80,
    LINESEQ,
    LINESEQ);

alignas(32) const __m256i PACK_HI_SEQ = _mm256_setr_epi8(
    LINESEQ,
    LINESEQ,
    0x01, 0x03, 0x05, -0x80,
    0x09, 0x0B, 0x0D, -0x80,
    LINESEQ,
    LINESEQ,
    0x11, 0x13, 0x15, -0x80,
    0x19, 0x1B, 0x1D, -0x80);
#undef LINESEQ

alignas(32) const __m256i NULLSEQ = _mm256_set1_epi8(0);

void calcBlending(uint8_t* dst, const uint8_t* bgr, const uint8_t* frt);

void calcBlending(uint8_t* dstPtr, const uint8_t* bgrPtr, const uint8_t* frtPtr) {
    __m256i bgr = _mm256_load_si256((const __m256i*)bgrPtr); // [b g r a][b g r a]<b g r a><b g r a>(b g r a)(b g r a){b g r a}{b g r a}
    __m256i frt = _mm256_load_si256((const __m256i*)frtPtr);
    __m256i dst = { 0 };

    // uint16_t alpha = frt[4];
    __m256i alpha = _mm256_shuffle_epi8(frt, ALPHASEQ); // [a a a 0][a a a 0]<a a a 0><a a a 0>(a a a 0)(a a a 0){a a a 0}{a a a 0}
    // uint16_t alphaRev = (uint16_t)(255 - alpha);
    __m256i alphaRev = _mm256_sub_epi8(ALPHA255SEQ, alpha);


    __m256i bgrHI = _mm256_unpackhi_epi8(bgr, NULLSEQ); // <b - g - r - a -><b - g - r - a ->{b - g - r - a -}{b - g - r - a -}
    __m256i bgrLO = _mm256_unpacklo_epi8(bgr, NULLSEQ); // [b - g - r - a -][b - g - r - a -](b - g - r - a -)(b - g - r - a -)
    __m256i frtHI = _mm256_unpackhi_epi8(frt, NULLSEQ);
    __m256i frtLO = _mm256_unpacklo_epi8(frt, NULLSEQ);
    __m256i alphaHI = _mm256_unpackhi_epi8(alpha, NULLSEQ);
    __m256i alphaLO = _mm256_unpacklo_epi8(alpha, NULLSEQ);
    __m256i alphaRevHI = _mm256_unpackhi_epi8(alphaRev, NULLSEQ);
    __m256i alphaRevLO = _mm256_unpacklo_epi8(alphaRev, NULLSEQ);


    bgrHI = _mm256_mullo_epi16(bgrHI, alphaRevHI); // <! b ! g ! r - -><! b ! g ! r - ->{! b ! g ! r - -}{! b ! g ! r - -}
    bgrLO = _mm256_mullo_epi16(bgrLO, alphaRevLO); // [! b ! g ! r - -][! b ! g ! r - -](! b ! g ! r - -)(! b ! g ! r - -)
    frtHI = _mm256_mullo_epi16(frtHI, alphaHI);
    frtLO = _mm256_mullo_epi16(frtLO, alphaLO);


    bgrHI = _mm256_shuffle_epi8(bgrHI, PACK_HI_SEQ);
    bgrLO = _mm256_shuffle_epi8(bgrLO, PACK_LO_SEQ);
    frtHI = _mm256_shuffle_epi8(frtHI, PACK_HI_SEQ);
    frtLO = _mm256_shuffle_epi8(frtLO, PACK_LO_SEQ);

    dst = _mm256_add_epi8(_mm256_or_si256(bgrHI, bgrLO), _mm256_or_si256(frtHI, frtLO));

    _mm256_store_si256((__m256i*)dstPtr, dst);
}

#define OFFSET COORD2INDEX(pxX, pxY, WINSIZEX, WINSIZEY, BYTECOUNT)

void blend(Mat image, const uint8_t* imgBgr, const uint8_t* imgFrt) {
    for (int32_t pxY = 0; pxY < WINSIZEY; ++pxY) {
        for (int32_t pxX = 0; pxX < WINSIZEX; pxX += BOOST_F) {

#ifdef MULTIPLY
            for (int32_t i = 0; i < MULTIPLY; ++i)
#endif
                calcBlending(image.data + OFFSET, imgBgr + OFFSET, imgFrt + OFFSET);
        }
    }
}

#undef OFFSET
