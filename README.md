# OP
Objektinis Programavimas

Testavimas atliekamas su tais pačiais failais iš 1000, 10000, 100000, 1000000, 10000000 įrašų.
Sistemos parametrai:
Intel i9-14900HX
32GB RAM
SSD 1000GB

Duomenų apdorojimas:

1 Strategija: Bendro studentai konteinerio skaidymas (rūšiavimas) į du naujus to paties tipo konteinerius: "vargsai" ir "kietakai". Tokiu būdu tas pats studentas yra dvejuose konteineriuose: bendrame studentai ir viename iš suskaidytų.

studentai1000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.0077 s  |  0.001011 s  |  0.002054 s  | 
| list  |  0.008208 s  |  0.003088 s  |  0.004201 s  |
| deque  |  0.009876 s  |  0.001121 s  |  0.003704 s  |


studentai10000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.068244 s  |  0.00516 s  |  0.035624 s  | 
| list  |  0.079761 s  |  0.132137 s  |  0.039012 s  |
| deque  |  0.062482 s  |   0.005202 s  |  0.041055 s  |


studentai100000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.633549 s  |  0.04709 s  |  0.411527 s  | 
| list |  0.799458 s  |  1.29775 s  |  0.462165 s |
| deque  |  0.596793 s  |   0.056836 s  |  0.572323 s  |


studentai1000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  6.35699 s  |  0.482504 s  |  5.62853 s  | 
| list  |  7.99817 s  |  1.33119 s  |  6.69815 s  |
| deque  |  6.04697 s  |  0.631405 s  |  7.67465 s  |


studentai10000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  64.58945 s  |  4.98756  |  55.64325 s  | 
| list |  81.75426 s  |  12.81321 s  |  65.89456 s  |
| deque  |  62.94478 s  |  5.15899 s  |  59.54568 s  |




2 Strategija: Bendro studentai konteinerio skaidymas (rūšiavimas) panaudojant tik vieną naują konteinerį "vargsai".

studentai1000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.009801 s  |  0.027614 s  |  0.002517 s  | 
| list  |  0.008385 s  |  0.001047 s  |  0.003058 s  |
| deque  |  0.005156 s  |  0.014375 s  |  0.004059 s  |


studentai10000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.071049 s  |  2.72454 s  |  0.033589 s  | 
| list  |  0.087688 s  |  0.011733 s  |  0.034489 s  |
| deque  |  0.066401 s  |   1.1099 s  |  0.043675 s  |


studentai100000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.638664 s  |  275.395 s  |  0.407074 s  | 
| list |  0.815418 s  |  0.09118 s  |  0.461479 s |
| deque  |  0.648705 s  |   113.235 s  |  0.564726 s  |


studentai1000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  -  |  -  |  -  | 
| list  |  7.99065 s  |  0.828697 s |  6.75767 s  |
| deque  |  -  |  -  |  -  |


studentai10000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  -  |  -  |  -  | 
| list |  8.14647 s  |  12.78521 s  |  65.15442 s  |
| deque  |  -  |  -  |  -  |


3 Strategija: Bendro studentai konteinerio skaidymas (rūšiavimas) į du naujus konteinerius, naudojant "efektyvius" darbo su konteineriais metodus.

studentai1000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.006716 s  |  0 s  |  0.002267 s  | 
| list  |  0.008385 s  |  0.001047 s  |  0.003058 s  |
| deque  |  0.005156 s  |  0.014375 s  |  0.004059 s  |


studentai10000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.06402 s  |  0.003833 s  |  0.030926 s  | 
| list  |  0.087688 s  |  0.011733 s  |  0.034489 s  |
| deque  |  0.066401 s  |   1.1099 s  |  0.043675 s  |


studentai100000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  0.658439 s  |  0.037274 s  |  0.411755 s  | 
| list |  0.815418 s  |  0.09118 s  |  0.461479 s |
| deque  |  0.648705 s  |   113.235 s  |  0.564726 s  |


studentai1000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  6.51211 s  |  0.389969 s  |  5.55069 s  | 
| list  |  7.99065 s  |  0.828697 s |  6.75767 s  |
| deque  |  -  |  -  |  -  |


studentai10000000.txt
| Konteineris | nuskaitymo trukmė  | skirstymo į dvi grupes trukmė | rūšiavimo didėjimo tvarka trukmė | 
|----|--------------------|-------------------------|--------------------------------|
| vector  |  64.58945 s  |  4.98756 s  |  55.64325 s  | 
| list |  8.14647 s  |  12.78521 s  |  65.15442 s  |
| deque  |  -  |  -  |  -  |
