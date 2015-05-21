
include RbConfig

case CONFIG['host_os']
when /mswin|windows|mingw32/i
    $HOST_OS = "windows"
when /darwin/i
    $HOST_OS = "darwin"
else
    abort("Unknown host config: Config::CONFIG['host_os']: #{Config::CONFIG['host_os']}")
end

$RAKE_ROOT = File.dirname(__FILE__)

ARTIFACTS_FOLDER = "#{$RAKE_ROOT}/Artifacts"

CMAKE_MACOSX_BUILD_FOLDER = "#{ARTIFACTS_FOLDER}/MacOSX_Build"
CMAKE_ANDROID_BUILD_FOLDER = "#{ARTIFACTS_FOLDER}/Android_Build"
CMAKE_IOS_BUILD_FOLDER = "#{ARTIFACTS_FOLDER}/IOS_Build"
CMAKE_WEB_BUILD_FOLDER = "#{ARTIFACTS_FOLDER}/Web_Build"

JSBIND_BIN_MACOSX = "#{CMAKE_MACOSX_BUILD_FOLDER}/Source/AtomicJS/JSBind/Release/JSBind"

namespace :build  do

  task :macosx_jsbind do

    if !Dir.exists?("#{CMAKE_MACOSX_BUILD_FOLDER}")
      FileUtils.mkdir_p(CMAKE_MACOSX_BUILD_FOLDER)
    end

    Dir.chdir(CMAKE_MACOSX_BUILD_FOLDER) do

      sh "cmake ../../ -G Xcode -DCMAKE_BUILD_TYPE=Release"
      sh "xcodebuild -target JSBind -configuration Release"

    end

  end

  #IOS MACOSX
  task :macosx do

    if !Dir.exists?("#{CMAKE_MACOSX_BUILD_FOLDER}")
      FileUtils.mkdir_p(CMAKE_MACOSX_BUILD_FOLDER)
    end

    Dir.chdir(CMAKE_MACOSX_BUILD_FOLDER) do

      sh "cmake ../../ -G Xcode -DCMAKE_BUILD_TYPE=Release"
      sh "xcodebuild -configuration Release"

    end

  end

  #IOS, dependent on macosx for JSBind
  task :ios =>  "build:macosx_jsbind" do

      if !Dir.exists?("#{CMAKE_IOS_BUILD_FOLDER}")
        FileUtils.mkdir_p(CMAKE_IOS_BUILD_FOLDER)
      end

      Dir.chdir(CMAKE_IOS_BUILD_FOLDER) do
        sh "#{JSBIND_BIN_MACOSX} #{$RAKE_ROOT} IOS"
        sh "cmake -DIOS=1 -DCMAKE_BUILD_TYPE=Release -G Xcode ../../"
        sh "xcodebuild -configuration Release"
      end

  end

  task :android =>  "build:macosx_jsbind" do

      if !Dir.exists?("#{CMAKE_ANDROID_BUILD_FOLDER}")
        FileUtils.mkdir_p(CMAKE_ANDROID_BUILD_FOLDER)
      end

      Dir.chdir(CMAKE_ANDROID_BUILD_FOLDER) do

        sh "#{JSBIND_BIN_MACOSX} #{$RAKE_ROOT} ANDROID"
        sh "cmake -DCMAKE_TOOLCHAIN_FILE=#{$RAKE_ROOT}/CMake/Toolchains/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release ../../"
        sh "make -j4"
      end

  end



end
