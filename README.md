# dmc-quant

A high-performance quantitative finance and algorithmic trading toolkit written in Demonic C.

This multi-module repository provides sub-microsecond trading primitives, financial protocol parsers, derivative pricing models with 256-bit SIMD acceleration, and real-time portfolio risk analytics.

---

## 🏛️ Architecture & Sub-Libraries

| Module | File | Capabilities |
|---|---|---|
| **LOB Engine** | `src/lob.dmc` | Price-time priority limit order book, market orders, cancelation, BBO, spread, mid-price, and VWAP tracking. |
| **Option Pricing** | `src/pricing.dmc` | Black-Scholes call/put pricing, Greeks (Delta, Gamma, Vega, Theta, Rho), Newton-Raphson implied volatility, Monte Carlo simulation, and 256-bit SIMD vector payoff calculation (`f32x8`). |
| **Technical Time-Series** | `src/timeseries.dmc` | Streaming statistical metrics: SMA, EMA, 14-period RSI, MACD lines, Bollinger Bands, rolling volatility, skewness, kurtosis, covariance, and correlation. |
| **Financial Protocols** | `src/fix.dmc` | Zero-overhead FIX 4.4 message builder and tag extractor (`NewOrderSingle`, `ExecutionReport`, checksum validation) and NASDAQ ITCH 5.0 binary packet decoder. |
| **Portfolio Risk Engine** | `src/risk.dmc` | Historical Value at Risk (VaR), Parametric VaR, Conditional VaR (Expected Shortfall), Sharpe Ratio, Sortino Ratio, Maximum Drawdown, and market Beta. |
| **Master Aggregator** | `src/dmc_quant.dmc` | Single entry point importing all five quantitative modules. |

---

## ⚡ Quick Start & Installation

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
```

---

## 🧪 Testing

Run the test suite across all 6 test suites:

```bash
dmc test tests
```

Output:
```
17/17 tests passed
Running 17 test(s) from 6 file(s)...

PASS tests\test_fix.dmc
PASS tests\test_lob.dmc
PASS tests\test_pricing.dmc
PASS tests\test_quant_all.dmc
PASS tests\test_risk.dmc
PASS tests\test_timeseries.dmc

Results: 6 passed, 0 failed
```
