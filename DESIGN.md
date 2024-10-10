Another encoding of Unicode is UTF-32, which encodes all Unicode code points in 4 bytes. For things like ASCII, the leading 3 bytes are all 0's. What are some tradeoffs between UTF-32 and UTF-8?

The tradeoffs are centered around memory usage, efficiency, and compatability. In UTF-8 characters are encoded using 1-4 bytes depending on the code point. In UTF-32 characters are encoded using 4 bytes regardless of the characters code point. Whilst UTF-32 might be more straight forward it uses significantly more memory that could have been saved, for instance ASCII characters.

UTF-8 has a leading 10 on all the bytes past the first for multi-byte code points. This seems wasteful – if the encoding for 3 bytes were instead 1110XXXX XXXXXXXX XXXXXXXX (where X can be any bit), that would fit 20 bits, which is over a million code points worth of space, removing the need for a 4-byte encoding. What are some tradeoffs or reasons the leading 10 might be useful? Can you think of anything that could go wrong with some programs if the encoding didn't include this restriction on multi-byte code points?

Continuation Bytes and start bytes could get confused with without the 10 pattern. The 10 pattern also preserves the integrity of ascii encoding by making it impossible for continuation bytes to overlap with the range of ascii characters. Without the 10 pattern security issues could arise as the continuation bytes would be less strictly defined and would make systems more vulnerable to attack.

