# dmc-quant

A high-performance quantitative finance, algorithmic trading, and portfolio engineering toolkit written in Demonic C.

This multi-module repository provides sub-microsecond trading primitives, zero-allocation financial protocol parsers, derivative pricing models with 256-bit SIMD acceleration, real-time risk analytics, algorithmic execution slicing, alpha factor modeling, and linear algebra routines.

---

## Architecture & Modules

| Module | File | Capabilities & Optimizations |
|---|---|---|
| **LOB Engine** | `src/lob.dmc` | Strict price-time priority (FIFO) limit order book (1024-order capacity), market orders, cancellation, BBO, spread, mid-price, VWAP, and Level-2 market depth extraction (`lob_level2_depth`). |
| **Option Pricing** | `src/pricing.dmc` | Black-Scholes analytical formulas, Greeks ($\Delta, \Gamma, \mathcal{V}, \Theta, \rho$), fast polynomial CDF approximation (`bs_fast_cnd`), 8-wide batch SIMD option pricing (`bs_batch_call8`, `bs_batch_put8`), Cox-Ross-Rubinstein American binomial tree (`crr_american_option`), Marsaglia Xorshift Monte Carlo (`bs_monte_carlo_fast`), and SIMD payoffs (`f32x8`). |
| **Technical Time-Series** | `src/timeseries.dmc` | Streaming statistical metrics: SMA, EMA, 14-period RSI, MACD lines, Bollinger Bands, rolling volatility, skewness, kurtosis, covariance, correlation, J.P. Morgan RiskMetrics EWMA volatility (`ts_ewma_volatility`), autocorrelation, rolling Z-score, and SIMD reductions (`ts_simd_dot`, `ts_simd_sum`). |
| **Financial Protocols** | `src/fix.dmc` | FIX 4.4 message serializer & checksum validator, zero-allocation fast field parsers (`fix_fast_get_int`, `fix_fast_get_float`), and NASDAQ ITCH 5.0 binary order book packet encoder/decoder (`itch_parse_add_order`). |
| **Portfolio Risk Engine** | `src/risk.dmc` | Historical Value at Risk (VaR), Parametric VaR, Conditional VaR (Expected Shortfall), Sharpe Ratio, Sortino Ratio, Maximum Drawdown, Calmar Ratio, market Beta, Omega ratio (`risk_omega_ratio`), and tail risk ratio (`risk_tail_ratio`). |
| **Portfolio Optimization** | `src/portfolio.dmc` | Markowitz 2-asset minimum variance, tangency (maximum Sharpe ratio), risk parity (inverse volatility), portfolio variance/return ($w^T \Sigma w$, $w^T R$), capital rebalancing share calculator, and Compound Annual Growth Rate (`port_cagr`). |
| **Algorithmic Execution** | `src/execution.dmc` | TWAP slice distribution, VWAP volume-weighted slicing, POV (percentage-of-volume) participation slicing, implementation shortfall, and slippage in basis points. |
| **Alpha Factors & ML** | `src/ml_factors.dmc` | Cross-sectional Z-score standardization, quantile winsorization, Ornstein-Uhlenbeck mean-reversion half-life, Information Coefficient (IC), percentile ranking (`factor_rank`), and Spearman rank correlation (`factor_spearman_ic`). |
| **SIMD Linear Algebra** | `src/simd_matrix.dmc` | 256-bit SIMD vector dot product (`simd_vector_dot8`), vector Euclidean norm (`simd_vector_norm8`), $4\times4$ matrix multiplication (`matrix_mul_4x4`), multi-asset covariance matrix estimation (`matrix_cov_from_returns`), Cholesky decomposition ($2\times2$ and $3\times3$), and $2\times2$ matrix inversion. |
| **Master Aggregator** | `src/dmc_quant.dmc` | Single unified entry point importing all nine quantitative modules. |

---

## Quick Start & Installation

Install directly into any Demonic C project via the package manager:

```bash
dmc pkg add https://github.com/ak495867/dmc-quant.git
```

Import all capabilities in one line:

```dmc
import "dmc_quant";
```

Or import individual sub-libraries as needed:

```dmc
import "lob";
import "pricing";
import "timeseries";
import "fix";
import "risk";
import "portfolio";
import "execution";
import "ml_factors";
import "simd_matrix";
```

---

## Benchmarks & Micro-Performance

Run the built-in benchmark harness:

```bash
dmc bench benchmarks
```

Measured throughput and latency:
```
bench_lob_matching:           0.006s (1,000 crossed orders matched & book updated)
bench_bs_analytical:          0.001s (10,000 analytical option pricings ~ 10M options/sec)
bench_bs_batch_simd:          0.006s (80,000 options priced via 256-bit SIMD)
bench_timeseries_sma_rsi:     0.000s (5,000 indicator ticks calculated)
bench_fix_parsing:            0.001s (2,000 zero-allocation FIX messages parsed)
bench_cholesky_factorization: 0.000s (10,000 matrix factorizations)

PASS benchmarks\bench_quant.dmc
```

---

## Testing

Run the test suite across all 10 test files:

```bash
dmc test tests
```

Output:
```
Running 32 test(s) from 10 file(s)...

PASS tests\test_execution.dmc
PASS tests\test_fix.dmc
PASS tests\test_lob.dmc
PASS tests\test_ml_factors.dmc
PASS tests\test_portfolio.dmc
PASS tests\test_pricing.dmc
PASS tests\test_quant_all.dmc
PASS tests\test_risk.dmc
PASS tests\test_simd_matrix.dmc
PASS tests\test_timeseries.dmc

Results: 10 passed, 0 failed
```
