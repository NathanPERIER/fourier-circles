
# Fourier circles

## Mathematical overview

The Fourier Transform is a kind of transformation that originates from the study of heat transfer and has found applications in various other fields, such as audio encoding. It allows to decompose a complex wave function into a sum of weighted pure frequencies. The general formula for computing the Fourier Transform $\widehat{f}$ of a given complex function $f : \mathbb{R} \to \mathbb{C}$ is as follows :

$$
{\widehat{f}}(\xi) = \int _{-\infty }^{\infty } f(t)\ e^{-i2\pi \xi t}\,dt
$$

The idea is that the function $f$ is coiled around a unit circle and that we then compute the centre of mass of all the points in this curve. The resulting value is generally quite low, except when the "coiling" $\xi$ matches the frequency of one pure signal that composes the function.

Note that the formula shown here is a limit when the bounds of the integral tend to infinity. When the function is assumed to be periodic, we can work on a closed interval.

One convenient property of complex numbers is that they can be plotted on a 2D graph. We can thus take a closed loop on the 2D plane and apply the Fourier Transform to the points of the curve. Basically, we consider that the points on the curve are the values of a complex periodic signal. We can then get the Fourier coefficients for this signal and apply the Inverse Fourier Transform to retrieve the original curve. If we remove the least-significant frequencies, we will get a curve that is close to the original. This is essentially lossy compression, and it is the same principle that lies behind the compression of audio signals.

Since we usually only get a finite quantity of samples from the curve, we can no longer rely on integration for the Fourier Transform. Instead, we will be applying a Discrete Fourier Transform, using a regular sum. Considering a sequence of $N$ complex samples $\left(x_n\right)_{0 \le n \le N-1}$ (evenly distributed in time), the computation of the coefficients $X_n$ is then defined as :

$$
\forall k \in \llbracket 0, N-1 \rrbracket, \quad X_{k} = \sum _{n=0}^{N-1}x_{n} \cdot e^{-i2\pi {\tfrac{k}{N}}n}
$$

More generally, we can write this as a function of "frequency" :

$$
\forall f \in \left[0, 1\right[, \quad X(f) = \sum _{n=0}^{N-1}x_{n} \cdot e^{-i2\pi fn}
$$

### Inverse transform

To retrieve the original function from the Fourier Transform, we can apply the Inverse Fourier Transform defined by :

$$
\forall \ t\in \mathbb {R}, \quad f(t) = \int _{-\infty }^{\infty }{\widehat{f}}(\xi)\ e^{i2\pi \xi t}\,d\xi
$$

In the case of the Discrete Fourier Transform, this translates to :

$$
\forall n \in \llbracket 0, N-1 \rrbracket, \quad x_{n} = {\frac {1}{N}}\sum _{k=0}^{N-1}X_{k}\cdot e^{i2\pi {\tfrac{k}{N}}n}
$$

One possible interpretation of this formula is that we are adding rotating vectors that have various lengths and rotation frequencies.

Note the presence of the $\frac{1}{N}$ factor. This is an adjustment to compensate for the fact that the Fourier Transform does not divide the sum of the complex points by the size of the input sequence when computing the "centre of mass".

We can also write this as a function of "time" :

$$
\forall t \in \left[0, 1\right[, \quad x(t) = {\frac {1}{N}}\sum _{k=0}^{N-1}X_{k}\cdot e^{i2\pi tk} = {\frac {1}{N}}\sum _{n_f=0}^{N_f-1}X\left(\tfrac{n_f}{N_f}\right)\cdot e^{i2\pi tn_f}
$$

Where $N_f \in \mathbb{R}^*_+$ can be assumed to be any large number. Using this formula, the sampling of the coefficients could theoretically be greater or smaller than the number of input points, but notice that the $\frac{1}{N}$ factor does not change. We could also remove some coefficients if they can be considered too insignificant.

## Useful references

Videos by 3Blue1Brown :

- [But what is the Fourier Transform? A visual introduction.](https://www.youtube.com/watch?v=spUNpyF58BY)
- [The more general uncertainty principle, regarding Fourier transforms](https://www.youtube.com/watch?v=MBnnXbOM5S4)
- [But what is a Fourier series? From heat flow to drawing with circles | DE4](https://www.youtube.com/watch?v=r6sGWTCMz2k)
