# Borrador del reporte — Partes 1 y 2 (Q1.1, Q1.2, Q2)

## Q1.1 — ¿Puede desbordar `orient`?

Con |x|, |y| ≤ 10⁹:

- Cada diferencia (por ejemplo `b.x − a.x`) cumple |·| ≤ 2·10⁹.
- Cada producto cumple |·| ≤ (2·10⁹)² = 4·10¹⁸.
- El resultado es la resta de dos productos, así que |orient| ≤ 4·10¹⁸ + 4·10¹⁸ = 8·10¹⁸.
- `long long` llega hasta 2⁶³ − 1 ≈ 9.22·10¹⁸. Como 8·10¹⁸ < 9.22·10¹⁸, **no hay desbordamiento** (ni en las restas, ni en los productos, ni en el resultado).

Si las coordenadas llegaran a 10¹⁰: diferencias ≤ 2·10¹⁰, productos ≤ 4·10²⁰, resultado ≤ 8·10²⁰, que **sí excede** 9.22·10¹⁸. Habría que calcular `orient` con `__int128` (rango ≈ 1.7·10³⁸) o con una biblioteca de enteros grandes.

## Q1.2 — Pops en `example13` y por qué el scan es O(n)

Orden angular alrededor de p0 = (312,56):
(684,86) (636,104) (720,170) (612,152) (576,194) (492,218) (420,200) (378,146) (402,224) (420,308) (288,170) (192,146)

Puntos que salen del stack, en orden (8 pops en total):

1. (636,104), al llegar (720,170)
2. (612,152), al llegar (576,194)
3. (576,194), al llegar (492,218)
4. (378,146), al llegar (402,224)
5. (420,200), al llegar (402,224)
6. (402,224), al llegar (420,308)
7. (492,218), al llegar (420,308)
8. (288,170), al llegar (192,146)

Quedan 5 vértices: (312,56), (684,86), (720,170), (420,308), (192,146).
(Pendiente: compararlo con la animación de las diapositivas.)

El scan es O(n) porque cada punto se mete al stack exactamente una vez (n pushes) y solo se puede sacar una vez, así que hay a lo sumo n pops en total. Aunque un `while` saque muchos puntos de golpe, el costo total se reparte (análisis amortizado): ≤ 2n operaciones de stack. El costo total de Graham, O(n log n), lo domina el ordenamiento.

## Q2 — Tests de orientación de Jarvis

En `example13.txt` (n = 13, h = 5), Jarvis hace **60 tests**.

Como función de n y h: **h·(n − 1)**. Por cada uno de los h vértices del hull, el ciclo interno recorre los n − 1 puntos distintos del actual y hace un test por cada uno (5 · 12 = 60). Es decir, Θ(n·h).

El peor caso es cuando **todos los puntos son vértices del hull** (h = n), por ejemplo n puntos sobre una circunferencia o sobre una parábola: n·(n − 1) = Θ(n²) tests (con n = 10⁵ serían ≈ 10¹⁰).
