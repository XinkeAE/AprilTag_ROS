/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <lcm/lcm_coretypes.h>

#ifndef __lcm_t_headers_quad_vscontrol_t_hpp__
#define __lcm_t_headers_quad_vscontrol_t_hpp__


namespace lcm_t_headers
{

class quad_vscontrol_t
{
    public:
        float      Roll;

        float      Pitch;

        float      Yaw_Meas;

        float      Thrust;

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to reqad while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "quad_vscontrol_t"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static int64_t _computeHash(const __lcm_hash_ptr *p);
};

int quad_vscontrol_t::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int quad_vscontrol_t::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int quad_vscontrol_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t quad_vscontrol_t::getHash()
{
    static int64_t hash = _computeHash(NULL);
    return hash;
}

const char* quad_vscontrol_t::getTypeName()
{
    return "quad_vscontrol_t";
}

int quad_vscontrol_t::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->Roll, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->Pitch, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->Yaw_Meas, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_encode_array(buf, offset + pos, maxlen - pos, &this->Thrust, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int quad_vscontrol_t::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->Roll, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->Pitch, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->Yaw_Meas, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __float_decode_array(buf, offset + pos, maxlen - pos, &this->Thrust, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int quad_vscontrol_t::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __float_encoded_array_size(NULL, 1);
    enc_size += __float_encoded_array_size(NULL, 1);
    enc_size += __float_encoded_array_size(NULL, 1);
    enc_size += __float_encoded_array_size(NULL, 1);
    return enc_size;
}

int64_t quad_vscontrol_t::_computeHash(const __lcm_hash_ptr *)
{
    int64_t hash = 0xbdbfd045cf9a78d8LL;
    return (hash<<1) + ((hash>>63)&1);
}

}

#endif