import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get stocks symbols and shares in a list
    stocks = db.execute("SELECT DISTINCT symbol FROM history WHERE user_id = ? ORDER BY symbol", session["user_id"])

    # get user's balance
    balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    balance = balance[0]["cash"]

    # preparing user's total balance
    total = balance

    # get names and prices
    for i in range(len(stocks)):
        stock = stocks[i]
        info = lookup(stock["symbol"])
        stock["name"] = info["name"]
        shares = db.execute("SELECT SUM(shares) FROM history WHERE user_id = ? AND symbol = ?", session["user_id"], stock["symbol"])
        stock["shares"] = shares[0]["SUM(shares)"]
        stock["price"] = info["price"]
        stock["value"] = stock["price"] * stock["shares"]
        total += stock["value"]

        # formating usd
        stock["price"] = usd(stock["price"])
        stock["value"] = usd(stock["value"])

    # formating usd
    balance = usd(balance)
    total = usd(total)

    return render_template("index.html", stocks=stocks, balance=balance, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        if not shares.isnumeric():
            return apology("Amount Must Be Number", 400)

        shares = float(shares)
        if not shares:
            return apology("Must Indicate Amount", 400)
        elif shares < 0:
            return apology("Amount Must Be More Than Zero", 400)
        elif (shares * 100) % 100 != 0:
            return apology("Amount Must Be An Integer", 400)
        else:
            try:
                result = lookup(request.form.get("symbol"))
                price = result["price"]
                symbol = result["symbol"]
                cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
                balance = cash[0]["cash"] - (price * int(shares))
                if balance > 0:
                    db.execute("INSERT INTO history (user_id, symbol, price, shares) VALUES (?, ?, ?, ?)",
                               session["user_id"], symbol, price, shares)
                    db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])
                    return redirect("/")
                else:
                    return apology("Inadequate Balance", 403)

            except:
                return apology("Invalid Symbol", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get stocks symbols and shares in a list
    history = db.execute("SELECT * FROM history WHERE user_id = ? ORDER BY time DESC", session["user_id"])

    # get names and prices
    for i in range(len(history)):
        trans = history[i]
        if trans["shares"] > 0:
            trans["type"] = "Buy"
        elif trans["shares"] < 0:
            trans["type"] = "Sell"
            trans["shares"] = trans["shares"] - (trans["shares"] * 2)

        # formating usd
        trans["price"] = usd(trans["price"])

    return render_template("history.html", trans=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        sym = request.form.get("symbol")

        try:
            result = lookup(sym)
            name = result["name"]
            price = usd(result["price"])
            symbol = result["symbol"]
            return render_template("quoted.html", name=name, price=price, symbol=symbol)

        except:
            return apology("Invalid Symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif password != confirmation:
            return apology("password confirm does not match", 400)
        elif len(db.execute("SELECT username FROM users WHERE username = ?", username)) != 0:
            return apology("this username is already taken", 400)

        hash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT DISTINCT symbol FROM history WHERE user_id = ? ORDER BY symbol", session["user_id"])
    stocks_list = []
    for stock in stocks:
        stocks_list.append(stock["symbol"])

    if request.method == "POST":
        # variables
        symbol = request.form.get("symbol")
        shares = float(request.form.get("shares"))
        own = db.execute("SELECT SUM(shares) FROM history WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        own = own[0]["SUM(shares)"]

        # check
        if not shares or shares < 0:
            return apology("Must Indicate Amount More Than Zero", 400)
        elif symbol not in stocks_list:
            return apology("You Do Not Have That Stock", 400)
        elif shares > own:
            return apology("You Do Not Have Enough Shares", 400)

        else:
            # db execute
            shares = 0 - shares
            price = lookup(symbol)["price"]
            db.execute("INSERT INTO history (user_id, symbol, price, shares) VALUES (?, ?, ?, ?)",
                       session["user_id"], symbol, price, shares)

            # update balance
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            balance = cash[0]["cash"] - (price * shares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

            return redirect("/")

    else:
        # get owned stock list
        return render_template("sell.html", stocks=stocks_list)