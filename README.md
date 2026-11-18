# dmc-quant

A high-performance quantitative finance, algorithmic trading, and portfolio engineering toolkit written in Demonic C.

This multi-module repository provides sub-microsecond trading primitives, financial protocol parsers, derivative pricing models with 256-bit SIMD acceleration, real-time risk analytics, algorithmic execution slicing, alpha factor modeling, and linear algebra routines.

---

## Architecture & Modules

| Module | File | Capabilities |
|---|---|---|
| **LOB Engine** | `src/lob.dmc` | Price-time priority limit order book, market orders, cancellation, BBO, spread, mid-price, and VWAP tracking. |
| **Option Pricing** | `src/pricing.dmc` | Black-Scholes call/put pricing, Greeks (Delta, Gamma, Vega, Theta, Rho), Newton-Raphson implied volatility, Monte Carlo simulation, and 256-bit SIMD vector payoff calculation (`f32x8`). |
| **Technical Time-Series** | `src/timeseries.dmc` | Streaming statistical metrics: SMA, EMA, 14-period RSI, MACD lines, Bollinger Bands, rolling volatility, skewness, kurtosis, covariance, and correlation. |
| **Financial Protocols** | `src/fix.dmc` | Zero-overhead FIX 4.4 message builder and tag extractor (`NewOrderSingle`, `ExecutionReport`, checksum validation) and NASDAQ ITCH 5.0 binary packet decoder. |
| **Portfolio Risk Engine** | `src/risk.dmc` | Historical Value at Risk (VaR), Parametric VaR, Conditional VaR (Expected Shortfall), Sharpe Ratio, Sortino Ratio, Maximum Drawdown, and market Beta. |
| **Portfolio Optimization** | `src/portfolio.dmc` | Markowitz 2-asset minimum variance, tangency (maximum Sharpe ratio), risk parity (inverse volatility), portfolio variance/return, and capital rebalancing share calculator. |
| **Algorithmic Execution** | `src/execution.dmc` | TWAP slice distribution, VWAP volume-weighted slicing, POV (percentage-of-volume) participation slicing, implementation shortfall, and slippage in basis points. |
| **Alpha Factors & ML** | `src/ml_factors.dmc` | Cross-sectional Z-score standardization, quantile winsorization, Ornstein-Uhlenbeck mean-reversion half-life, and Information Coefficient (IC). |
| **SIMD Linear Algebra** | `src/simd_matrix.dmc` | 256-bit SIMD vector dot product (`simd_vector_dot8`), Cholesky decomposition ($2\times2$ and $3\times3$), $2\times2$ matrix inversion, and $3\times3$ matrix-vector multiplication. |
| **Master Aggregator** | `src/dmc_quant.dmc` | Single entry point importing all nine quantitative modules. |

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

## Testing

Run the test suite across all 10 test files:

```bash
dmc test tests
```

Output:
```
Running 26 test(s) from 10 file(s)...

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
