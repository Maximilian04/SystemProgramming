Alphabet:       db "0123456789ABCDEF"           ; Alphabet for printing (Thanks Ilya)
BoxSymbols:     db 0c9h, 0cdh, 0bbh, 0bah, 0bch, 0c8h ; "╔═╗║╝╚"

BoxAssetLU:     db 020h, 0dah, 0c9h, 000h
BoxAsset_U:     db 020h, 0c4h, 0cdh, 000h
BoxAssetRU:     db 020h, 0bfh, 0bbh, 000h
BoxAssetR_:     db 020h, 0b3h, 0bah, 000h
BoxAssetRB:     db 020h, 0d9h, 0bch, 000h
BoxAsset_B:     db 020h, 0c4h, 0cdh, 000h
BoxAssetLB:     db 020h, 0c0h, 0c8h, 000h
BoxAssetL_:     db 020h, 0b3h, 0bah, 000h
BoxAssetFI:     db 020h, 020h, 020h, 000h

; 0:    1:┌─┐ 2:╔═╗ 3:usr
;         │ │   ║ ║   chr
;         └─┘   ╚═╝
