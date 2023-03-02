Alphabet:       db "0123456789ABCDEF"           ; Alphabet for printing (Thanks Ilya)
BoxSymbols:     db 0c9h, 0cdh, 0bbh, 0bah, 0bch, 0c8h ; "╔═╗║╝╚"

BoxAssetLU:     db 020h, 0dah, 0c9h
BoxAsset_U:     db 020h, 0c4h, 0cdh
BoxAssetRU:     db 020h, 0bfh, 0bbh
BoxAssetR_:     db 020h, 0b3h, 0bah
BoxAssetRB:     db 020h, 0d9h, 0bch
BoxAsset_B:     db 020h, 0c4h, 0cdh
BoxAssetLB:     db 020h, 0c0h, 0c8h
BoxAssetL_:     db 020h, 0b3h, 0bah
BoxAssetFI:     db 020h, 020h, 020h

; 0:    1:┌─┐ 2:╔═╗
;         │ │   ║ ║
;         └─┘   ╚═╝
