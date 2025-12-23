#include "graph.hpp"
#include <iostream>
#include <iomanip>

bool generateInvestmentChart(investment& inv, std::string filename) {
    if (inv.monthly_values.size() < 2) {
        std::cout << "\nNot enough data to generate chart. Complete a simulation first.\n";
        return false;
    }

    try {
        // Prepare x-axis (months)
        std::vector<double> months;
        for (size_t i = 0; i < inv.monthly_values.size(); i++) {
            months.push_back(static_cast<double>(i));
        }

        // Prepare y-axis (portfolio values)
        std::vector<double> values;
        
        for (size_t i = 0; i < inv.monthly_values.size(); i++) {
            values.push_back(static_cast<double>(inv.monthly_values[i]));
        }

        // Create the plot
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *errorMessage = CreateStringReference(toVector(L""));
        
        ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
        settings->width = 800;
        settings->height = 600;
        settings->autoBoundaries = true;
        settings->autoPadding = true;
        settings->title = toVector(L"Investment Growth Over Time");
        settings->xLabel = toVector(L"Month");
        settings->yLabel = toVector(L"Portfolio Value ($)");
        settings->showGrid = true;
        
        // Configure series
        settings->scatterPlotSeries = new std::vector<ScatterPlotSeries*>(1);
        settings->scatterPlotSeries->at(0) = GetDefaultScatterPlotSeriesSettings();
        settings->scatterPlotSeries->at(0)->xs = &months;
        settings->scatterPlotSeries->at(0)->ys = &values;
        settings->scatterPlotSeries->at(0)->linearInterpolation = true;
        settings->scatterPlotSeries->at(0)->lineType = toVector(L"solid");
        settings->scatterPlotSeries->at(0)->lineThickness = 2.0;
        settings->scatterPlotSeries->at(0)->color = CreateRGBColor(0.2, 0.4, 0.8);

        bool success = DrawScatterPlotFromSettings(imageRef, settings, errorMessage);

        if (success) {
            // Convert to PNG
            std::vector<double> *pngData = ConvertToPNG(imageRef->image);
            WriteToFile(pngData, filename);
            delete pngData;
            
            DeleteImage(imageRef->image);
            return true;
        } else {
            std::cout << "\nError generating chart: ";
            for (size_t i = 0; i < errorMessage->string->size(); i++) {
                std::cout << (char)errorMessage->string->at(i);
            }
            std::cout << "\n";
            return false;
        }

    } catch (...) {
        std::cout << "\nException occurred while generating chart.\n";
        return false;
    }
}

bool generateComparisonChart(investment& inv, std::string filename) {
    if (inv.monthly_values.size() == 0) {
        std::cout << "\nNo investment data available. Complete a simulation first.\n";
        return false;
    }

    try {
        // Prepare data: Initial Investment, Total Contributed, Final Value
        std::vector<double> values;
        values.push_back(static_cast<double>(inv.initial_amount));
        values.push_back(static_cast<double>(inv.total_amount));
        values.push_back(static_cast<double>(inv.current_amount));

        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *errorMessage = CreateStringReference(toVector(L""));

        BarPlotSettings *settings = GetDefaultBarPlotSettings();
        settings->width = 800;
        settings->height = 600;
        settings->autoBoundaries = true;
        settings->autoPadding = true;
        settings->title = toVector(L"Investment Comparison");
        settings->yLabel = toVector(L"Amount ($)");
        settings->showGrid = true;
        settings->autoColor = true;
        settings->barBorder = true;
        
        // Configure labels
        settings->autoLabels = false;
        settings->xLabels = new std::vector<StringReference*>(3);
        settings->xLabels->at(0) = CreateStringReference(toVector(L"Initial"));
        settings->xLabels->at(1) = CreateStringReference(toVector(L"Total Invested"));
        settings->xLabels->at(2) = CreateStringReference(toVector(L"Final Value"));

        // Configure series
        settings->barPlotSeries = new std::vector<BarPlotSeries*>(1);
        settings->barPlotSeries->at(0) = GetDefaultBarPlotSeriesSettings();
        settings->barPlotSeries->at(0)->ys = &values;

        bool success = DrawBarPlotFromSettings(imageRef, settings, errorMessage);

        if (success) {
            std::vector<double> *pngData = ConvertToPNG(imageRef->image);
            WriteToFile(pngData, filename);
            delete pngData;
            
            DeleteImage(imageRef->image);
            return true;
        } else {
            std::cout << "\nError generating comparison chart.\n";
            return false;
        }

    } catch (...) {
        std::cout << "\nException occurred while generating comparison chart.\n";
        return false;
    }
}

void displayChartStatus(bool success, std::string filename) {
    if (success) {
        std::cout << "\n✓ Chart successfully generated: " << filename << "\n";
        std::cout << "  You can view this file using any image viewer.\n";
    } else {
        std::cout << "\n✗ Failed to generate chart: " << filename << "\n";
    }
}