#include <ql/quantlib.hpp>
#include <iostream>

void example_option_1() {

    QuantLib::Calendar calendar = QuantLib::TARGET();
    QuantLib::Date todaysDate(6, QuantLib::Dec, 2018);
    QuantLib::Date settlementDate(6, QuantLib::Dec, 2018);
    QuantLib::Date maturity(6, QuantLib::Dec, 2019);

    QuantLib::Option::Type OptionType(QuantLib::Option::Call);
    QuantLib::Real stock = 100.00;
    QuantLib::Real strike = 90.00;
    QuantLib::Spread dividendYield = 0.00;
    QuantLib::Rate riskFreeRate = 0.05;
    QuantLib::Volatility volatility = 0.20;

    QuantLib::Settings::instance().evaluationDate() = todaysDate;

    boost::shared_ptr<QuantLib::Exercise> europeanExercise(
        new QuantLib::EuropeanExercise(maturity));
    boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
        new QuantLib::PlainVanillaPayoff(OptionType, strike));

    QuantLib::VanillaOption europeanOption(payoff, europeanExercise);


    // boost::shared_ptr<QuantLib::Quote> ptr_spotPrice(new QuantLib::SimpleQuote(stock));
    // QuantLib::Handle<QuantLib::Quote> spotPrice(ptr_spotPrice);
    // equivalent to
    QuantLib::Handle<QuantLib::Quote> spotPrice(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(stock)));

    QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();
    QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));

    QuantLib::Handle<QuantLib::YieldTermStructure> flatTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));

    QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility, dayCounter)));

    boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
        new QuantLib::BlackScholesMertonProcess(spotPrice, flatDividendTS, flatTS, flatVolTS));

    boost::shared_ptr<QuantLib::PricingEngine> Engine(
        new QuantLib::AnalyticEuropeanEngine(bsmProcess));

    europeanOption.setPricingEngine(Engine);
    QuantLib::Real pv = europeanOption.NPV();

    std::cout << "Option Start Date = " << todaysDate << std::endl;
    std::cout << "Option Settlement Date = " << settlementDate << std::endl;
    std::cout << "Option Maturity Date = " << maturity << std::endl;
    std::cout << "Option Type = " << OptionType << std::endl;
    std::cout << "Stock Price = " << stock << std::endl;
    std::cout << "Strike Price = " << strike << std::endl;
    std::cout << "Risk Free Rate = " << riskFreeRate << std::endl;
    std::cout << "Dividend Yield = " << dividendYield << std::endl;
    std::cout << "Volatility = " << volatility << std::endl;
    std::cout << "European Option Price = " << europeanOption.NPV() << std::endl;
}

void example_option_2() {
    // same as example_option_1,
    // copied from https://benjaminwhiteside.com/2018/12/11/implementing-a-quantlib-pricing-engine/
    // Date Stuff
    QuantLib::Calendar calendar = QuantLib::TARGET();
    QuantLib::Date todaysDate(6, QuantLib::December, 2018);
    QuantLib::Date settlementDate(6, QuantLib::December, 2018);
    QuantLib::Date maturity(6, QuantLib::December, 2019);
    QuantLib::DayCounter dayCounter = QuantLib::Actual365Fixed();
    // Initial Values
    QuantLib::Option::Type OptionType(QuantLib::Option::Call);
    QuantLib::Real stock = 100.00;
    QuantLib::Real strike = 90.00;
    QuantLib::Spread dividendYield = 0.00;
    QuantLib::Rate riskFreeRate = 0.05;
    QuantLib::Volatility volatility = 0.20;

    QuantLib::Settings::instance().evaluationDate() = todaysDate;

    // Creation of Exercise and Payoff objects:
    boost::shared_ptr<QuantLib::Exercise> europeanExercise(
        new QuantLib::EuropeanExercise(maturity));
    boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff(
        new QuantLib::PlainVanillaPayoff(OptionType, strike));
    // Create the European Option (Instrument) object:
    QuantLib::VanillaOption europeanOption(payoff, europeanExercise);

    // Variable Handles for the Stochastic (BSM) Process declaration (incuding Flat Term
    // Structures):
    QuantLib::Handle<QuantLib::Quote> spotPrice(
        boost::shared_ptr<QuantLib::Quote>(new QuantLib::SimpleQuote(stock)));
    QuantLib::Handle<QuantLib::YieldTermStructure> flatDividendTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, dividendYield, dayCounter)));
    QuantLib::Handle<QuantLib::YieldTermStructure> flatTS(
        boost::shared_ptr<QuantLib::YieldTermStructure>(
            new QuantLib::FlatForward(settlementDate, riskFreeRate, dayCounter)));
    QuantLib::Handle<QuantLib::BlackVolTermStructure> flatVolTS(
        boost::shared_ptr<QuantLib::BlackVolTermStructure>(
            new QuantLib::BlackConstantVol(settlementDate, calendar, volatility, dayCounter)));

    // Creation of the Underlying (1-d) Stochastic Process:
    boost::shared_ptr<QuantLib::BlackScholesMertonProcess> bsmProcess(
        new QuantLib::BlackScholesMertonProcess(spotPrice, flatDividendTS, flatTS, flatVolTS));
    // Creation of the Pricing Engine:
    boost::shared_ptr<QuantLib::PricingEngine> Engine(
        new QuantLib::AnalyticEuropeanEngine(bsmProcess));
    // Set the Pricing Engine:
    europeanOption.setPricingEngine(Engine);

    // Output Results:
    std::cout << "Option Start Date = " << todaysDate << std::endl;
    std::cout << "Option Settlement Date = " << settlementDate << std::endl;
    std::cout << "Option Maturity Date = " << maturity << std::endl;
    std::cout << "Option Type = " << OptionType << std::endl;
    std::cout << "Stock Price = " << stock << std::endl;
    std::cout << "Strike Price = " << strike << std::endl;
    std::cout << "Risk Free Rate = " << riskFreeRate << std::endl;
    std::cout << "Dividend Yield = " << dividendYield << std::endl;
    std::cout << "Volatility = " << volatility << std::endl;

    std::cout << "European Option Price = " << europeanOption.NPV() << std::endl;
}

using namespace QuantLib;
void example_option_3() {
    // set up dates
    Calendar calendar = TARGET();
    Date todaysDate(15, May, 1998);
    Date settlementDate(17, May, 1998);
    Settings::instance().evaluationDate() = todaysDate;

    // our options
    Option::Type type(Option::Put);
    Real underlying = 36;
    Real strike = 40;
    Spread dividendYield = 0.00;
    Rate riskFreeRate = 0.06;
    Volatility volatility = 0.20;
    Date maturity(17, May, 1999);
    DayCounter dayCounter = Actual365Fixed();

    std::cout << "Option type = " << type << std::endl;
    std::cout << "Maturity = " << maturity << std::endl;
    std::cout << "Underlying price = " << underlying << std::endl;
    std::cout << "Strike = " << strike << std::endl;
    std::cout << "Risk-free interest rate = " << io::rate(riskFreeRate) << std::endl;
    std::cout << "Dividend yield = " << io::rate(dividendYield) << std::endl;
    std::cout << "Volatility = " << io::volatility(volatility) << std::endl;
    std::cout << std::endl;
    std::string method;
    std::cout << std::endl;

    // write column headings
    Size widths[] = {35, 14, 14, 14};
    std::cout << std::setw(widths[0]) << std::left << "Method" << std::setw(widths[1]) << std::left
              << "European" << std::setw(widths[2]) << std::left << "Bermudan"
              << std::setw(widths[3]) << std::left << "American" << std::endl;

    std::vector<Date> exerciseDates;
    for (Integer i = 1; i <= 4; i++)
        exerciseDates.push_back(settlementDate + 3 * i * Months);

    ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));

    ext::shared_ptr<Exercise> bermudanExercise(new BermudanExercise(exerciseDates));

    ext::shared_ptr<Exercise> americanExercise(new AmericanExercise(settlementDate, maturity));

    Handle<Quote> underlyingH(ext::shared_ptr<Quote>(new SimpleQuote(underlying)));

    // bootstrap the yield/dividend/vol curves
    Handle<YieldTermStructure> flatTermStructure(ext::shared_ptr<YieldTermStructure>(
        new FlatForward(settlementDate, riskFreeRate, dayCounter)));
    Handle<YieldTermStructure> flatDividendTS(ext::shared_ptr<YieldTermStructure>(
        new FlatForward(settlementDate, dividendYield, dayCounter)));
    Handle<BlackVolTermStructure> flatVolTS(ext::shared_ptr<BlackVolTermStructure>(
        new BlackConstantVol(settlementDate, calendar, volatility, dayCounter)));
    ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));
    ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(
        new BlackScholesMertonProcess(underlyingH, flatDividendTS, flatTermStructure, flatVolTS));

    // options
    VanillaOption europeanOption(payoff, europeanExercise);
    VanillaOption bermudanOption(payoff, bermudanExercise);
    VanillaOption americanOption(payoff, americanExercise);

    // Analytic formulas:

    // Black-Scholes for European
    method = "Black-Scholes";
    europeanOption.setPricingEngine(
        ext::shared_ptr<PricingEngine>(new AnalyticEuropeanEngine(bsmProcess)));
    std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1])
              << std::left << europeanOption.NPV() << std::setw(widths[2]) << std::left << "N/A"
              << std::setw(widths[3]) << std::left << "N/A" << std::endl;
}


int main() {


    QuantLib::Calendar myCal = QuantLib::UnitedKingdom();
    QuantLib::Date newYearsEve(31, QuantLib::Dec, 2008);
    
    std::cout << "Name: " << myCal.name() << std::endl;
    std::cout << "New Year is Holiday: " << myCal.isHoliday(newYearsEve) << std::endl;
    std::cout << "New Year is Business Day: " << myCal.isBusinessDay(newYearsEve) << std::endl;

    std::cout << "--------------- Date Counter --------------------" << std::endl;

    QuantLib::Date date1(28, QuantLib::Dec, 2008);
    QuantLib::Date date2(04, QuantLib::Jan, 2009);

    std::cout << "First Date: " << date1 << std::endl;
    std::cout << "Second Date: " << date2 << std::endl;
    std::cout << "Business Days Betweeen: " << myCal.businessDaysBetween(date1, date2) << std::endl;
    std::cout << "End of Month 1. Date: " << myCal.endOfMonth(date1) << std::endl;
    std::cout << "End of Month 2. Date: " << myCal.endOfMonth(date2);

    std::cout << " \n=============== New tests ================== \n";

    example_option_1();
    example_option_2();
    example_option_3();

    return 0;
}