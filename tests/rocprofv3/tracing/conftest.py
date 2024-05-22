#!/usr/bin/env python3

import csv
import pytest
import json

from rocprofiler_sdk.pytest_utils.dotdict import dotdict
from rocprofiler_sdk.pytest_utils import collapse_dict_list


def pytest_addoption(parser):
    parser.addoption(
        "--agent-input",
        action="store",
        help="Path to agent info CSV file.",
    )
    parser.addoption(
        "--hsa-input",
        action="store",
        help="Path to HSA API tracing CSV file.",
    )
    parser.addoption(
        "--kernel-input",
        action="store",
        help="Path to kernel tracing CSV file.",
    )
    parser.addoption(
        "--memory-copy-input",
        action="store",
        help="Path to memory-copy tracing CSV file.",
    )
    parser.addoption(
        "--marker-input",
        action="store",
        help="Path to marker API tracing CSV file.",
    )
    parser.addoption(
        "--hip-input",
        action="store",
        help="Path to HIP runtime and compiler API tracing CSV file.",
    )
    parser.addoption(
        "--json-input",
        action="store",
        help="Path to JSON file.",
    )


@pytest.fixture
def agent_info_input_data(request):
    filename = request.config.getoption("--agent-input")
    data = []
    with open(filename, "r") as inp:
        reader = csv.DictReader(inp)
        for row in reader:
            data.append(row)

    return data


@pytest.fixture
def hsa_input_data(request):
    filename = request.config.getoption("--hsa-input")
    data = []
    with open(filename, "r") as inp:
        reader = csv.DictReader(inp)
        for row in reader:
            data.append(row)

    return data


@pytest.fixture
def kernel_input_data(request):
    filename = request.config.getoption("--kernel-input")
    data = []
    with open(filename, "r") as inp:
        reader = csv.DictReader(inp)
        for row in reader:
            data.append(row)

    return data


@pytest.fixture
def memory_copy_input_data(request):
    filename = request.config.getoption("--memory-copy-input")
    data = []
    with open(filename, "r") as inp:
        reader = csv.DictReader(inp)
        for row in reader:
            data.append(row)

    return data


@pytest.fixture
def marker_input_data(request):
    filename = request.config.getoption("--marker-input")
    data = []
    with open(filename, "r") as inp:
        reader = csv.DictReader(inp)
        for row in reader:
            data.append(row)

    return data


@pytest.fixture
def hip_input_data(request):
    filename = request.config.getoption("--hip-input")
    data = []
    with open(filename, "r") as inp:
        reader = csv.DictReader(inp)
        for row in reader:
            data.append(row)

    return data


@pytest.fixture
def json_data(request):
    filename = request.config.getoption("--json-input")
    with open(filename, "r") as inp:
        return dotdict(collapse_dict_list(json.load(inp)))
