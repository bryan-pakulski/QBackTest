# Converts data from various exchanges to a universal format
def binance_k_lines():
    columns = [
        "Open time", "Open", "High", "Low", "Close", "Volume", "Close time", "Quote asset volume", "Number of trades",
        "Taker buy base asset volume", "Taker buy quote asset volume", "Ignore"
    ]

    mapping = {
        "Open time": "OpenTime",
        "Close time": "CloseTime",
        "Open": "Open",
        "Close": "Close",
        "High": "High",
        "Low": "Low",
        "Volume": "Volume"
    }

def main():
    print("Hello World!")


if __name__ == "__main__":
    main()
