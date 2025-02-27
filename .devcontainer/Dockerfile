#############################################################################################################
# To build container:
#       docker build -t USER_NAME/CONTAINER_NAME:VERSION_NUMB -t USER_NAME/CONTAINER_NAME:latest .
#   example:
#       docker build -t niwciu/stm32_dev_container:1.0.0 -t niwciu/stm32_dev_container:latest .
# To push the container:
#       docker push USER_NAME/CONTAINER_NAME:VERSION_NUMB  
#       docker push USER_NAME/CONTAINER_NAME:latest
#   example:
#       docker push niwciu/stm32_dev_container:latest
#       docker push niwciu/stm32_dev_container:1.0.0
#
############################################################################################################
FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    g++ \
    git \
    ninja-build \
    wget \
    xz-utils \
    python3 \
    python3-venv \
    python3-pip \
    pipx \
    make \
    clang-format \
    stlink-tools \
    graphviz && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Ensure pipx installs globally and is available for all users
ENV PIPX_BIN_DIR=/usr/local/bin
ENV PIPX_HOME=/usr/local/pipx
ENV PATH="${PIPX_BIN_DIR}:${PIPX_HOME}/bin:${PATH}"

RUN pipx install --system-site-packages lizard && \
    pipx install --system-site-packages gcovr && \
    pipx runpip lizard install jinja2

# Ensure all users can access installed tools
RUN chmod -R a+rx /usr/local/bin /usr/local/pipx

# Set tools directory
ARG TOOLS_DIRECTORY=/opt/tools
RUN mkdir -p ${TOOLS_DIRECTORY} && chmod -R a+rx ${TOOLS_DIRECTORY}

# Install ARM toolchain
ARG ARM_TOOLCHAIN_VERSION=13.2
ARG ARM_TOOLCHAIN_FILE=arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}.rel1-x86_64-arm-none-eabi.tar.xz
ARG ARM_TOOLCHAIN_DIRECTORY=arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}.Rel1-x86_64-arm-none-eabi

RUN wget -q https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}.rel1/binrel/${ARM_TOOLCHAIN_FILE} && \
    tar xf ${ARM_TOOLCHAIN_FILE} -C ${TOOLS_DIRECTORY} && \
    rm ${ARM_TOOLCHAIN_FILE}

ENV PATH="${PATH}:${TOOLS_DIRECTORY}/${ARM_TOOLCHAIN_DIRECTORY}/bin"

# Install cppcheck
ARG CPPCHECK_VERSION=2.16.2
RUN git clone https://github.com/danmar/cppcheck.git /tmp/cppcheck && \
    cd /tmp/cppcheck && git checkout ${CPPCHECK_VERSION} && \
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DUSE_MATCHCOMPILER=ON -G Ninja && \
    cmake --build build && cmake --install build && \
    rm -rf /tmp/cppcheck

# Install latest Doxygen from source
ARG DOXYGEN_VERSION=1.13.2
ARG DOXYGEN_FILE=doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz
ARG DOXYGEN_DIRECTORY=doxygen-${DOXYGEN_VERSION}

RUN wget -q https://www.doxygen.nl/files/doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz && \
    tar xf ${DOXYGEN_FILE} -C ${TOOLS_DIRECTORY} && \
    rm ${DOXYGEN_FILE}


# Install latest Doxygen from source
ARG DOXYGEN_VERSION=1.13.2
ARG DOXYGEN_FILE=doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz
ARG DOXYGEN_DIRECTORY=doxygen-${DOXYGEN_VERSION}

# Pobieranie i rozpakowywanie Doxygena
RUN wget -q https://www.doxygen.nl/files/doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz && \
    tar xf ${DOXYGEN_FILE} -C ${TOOLS_DIRECTORY} && \
    rm ${DOXYGEN_FILE}

# Ustawienie zmiennych ścieżek
ENV DOXYGEN_BIN_DIR=${TOOLS_DIRECTORY}/${DOXYGEN_DIRECTORY}/bin

# Dodanie ścieżki do Doxygena w systemie PATH
ENV PATH="${PATH}:${DOXYGEN_BIN_DIR}"

# Ustawienie domyślnego powłoki
CMD ["/bin/bash"]


