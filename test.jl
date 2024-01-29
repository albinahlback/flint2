function lowparts(ap::Vector{UInt128}, bp::Vector{UInt128})
    for ix in 1:length(ap)
        for jx in 1:length(bp)
            tmp = BigInt(ap[ix]) * BigInt(bp[ix])
            println("ix = $(ix - 1), jx = $(jx - 1): L = ", unsafe_load(tmp.d, 1))
        end
    end
end

function highparts(ap::Vector{UInt128}, bp::Vector{UInt128})
    for ix in 1:length(ap)
        for jx in 1:length(bp)
            tmp = BigInt(ap[ix]) * BigInt(bp[ix])
            println("ix = $(ix - 1), jx = $(jx - 1): L = ", unsafe_load(tmp.d, 2))
        end
    end
end
