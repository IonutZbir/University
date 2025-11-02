"use strict";
import chalk from 'chalk';

const error = "ERROR";
const warning = "WARNING";
const info = "INFO";

const log = (message, level = info) => {
    switch (level) {
        case error:
            console.log(chalk.red(`[${level}] ${message}`));
            break;
        case warning:
            console.log(chalk.yellow(`[${level}] ${message}`));
            break;
        case info:
            console.log(chalk.blue(`[${level}] ${message}`));
            break;
        default:
            console.log(message);
    }
};

export {log, error, warning, info}
