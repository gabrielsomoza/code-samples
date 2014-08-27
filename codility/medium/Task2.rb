#
# Task Name: QmFzZU5lZzJPZkludA==
#
# === RESULTS ===
# Used time: 31 minutes
# Score: 100/100
# Complexity: O(log(M))
#
def solution(m)
    result = []
    return result if (m == 0)

    # Ruby doesn't allow negative radixes for r on Fixnum.to_s(r)
    # so we need to implement a generic base conversion method manually
    while m != 0
        m, rem = m.divmod(-2)
        if rem < 0
            m += 1
            rem += 2
        end
        result << rem
    end
    result
end