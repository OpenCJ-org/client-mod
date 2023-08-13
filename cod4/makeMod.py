import os
import sys
import subprocess
import shutil

# Bunch of paths
opencj_cod4_dir = os.getcwd()
opencj_dir = os.path.join(opencj_cod4_dir, '..\\')
root_dir = os.path.join(opencj_cod4_dir, '..\\..\\..\\')
raw_dir = os.path.join(root_dir, 'raw')
bin_dir = os.path.join(root_dir, 'bin')
zone_source_dir = os.path.join(root_dir, 'zone_source')
zone_dir = os.path.join(root_dir, 'zone')
tmp_dir = os.path.join(opencj_cod4_dir, 'tmp')
opencj_iwd_name = 'z_opencj'
opencj_ff = 'mod.ff'


def fatal_exit(str):
    print('\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\nFATAL: {}\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n'.format(str))
    cd(opencj_cod4_dir) # Don't end up in a random folder upon error
    if os.path.exists(tmp_dir):
        shutil.rmtree(tmp_dir) # Always delete the tmp directory
    sys.exit(1)


def cd(path):
    try:
        os.chdir(path)
    except (WindowsError, OSError) as e:
        fatal_exit('Could not cd to: {}'.format(path))


def rmfile(path):
    if os.path.exists(path):
        os.remove(path)

def mkdir(path, force=False):
    if os.path.exists(path) and os.path.isdir(path):
        if force:
            os.rmdir(path)
        else:
            fatal_exit('Failed to remove directory: {} (force={})'.format(path, force))
    os.mkdir(path)


def cp_contents(src, dst):
    # Copy contents of the src folder into dst directly
    try:
        os.makedirs(src, exist_ok=True)
        shutil.copytree(src, dst, dirs_exist_ok=True)
    except Exception as e:
        print(e)
        fatal_exit('Failed to contents of folder {} into {}'.format(src, dst))


def cmd(cmd_list):
    try:
        result = subprocess.run(cmd_list, capture_output=True, text=True, check=True)
    except subprocess.CalledProcessError as cpe:
        fatal_exit('Command: {}   failed with error: {}'.format(cmd_list, result.stderr))


def clear():
    os.system('cls' if os.name == 'nt' else 'clear')


def main():
    clear()
    print('Important: this script needs to be in <game>/mods/opencj/cod4 folder for the paths to work\n')

    # We start in a subdir where we need files from, but the output needs to be in parent directory so the fs_game works
    cd(opencj_dir)

    # Remove any existing output files so if the build fails you can't accidentally use the existing files
    rmfile(opencj_iwd_name + '.iwd')
    rmfile(opencj_ff)

    # Copy over all files to raw so the mod tools can do their job
    ff_folders = ['opencj','animtrees','english','fx','images','maps','material_properties','materials','info','mp','soundaliases','sound','ui','ui_mp','weapons','vision','xanim','xmodel','xmodelparts','xmodelsurfs']
    folders_copied = 0
    for folder in ff_folders:
        # Only copy it if it exists
        full_path = os.path.join(opencj_cod4_dir, folder)
        raw_subdir = os.path.join(raw_dir, folder)
        if os.path.exists(full_path):
            cp_contents(full_path, raw_subdir)
            folders_copied += 1
    
    # If no folders were copied, this is probably not the right directory
    if folders_copied == 0:
        fatal_exit('None of the .ff folders were found in {}'.format(opencj_cod4_dir))

    # Copy the mod.csv so the mod tools know which files are used by the mod
    mod_csv = 'mod.csv'
    mod_csv_path = os.path.join(opencj_cod4_dir, mod_csv)
    try:
        shutil.copyfile(mod_csv_path, os.path.join(zone_dir, mod_csv))
    except Exception as e:
        fatal_exit('Could not copy {} to {}'.format(mod_csv_path, zone_dir))
    
    # Now head to the Modtools bin folder and get to work
    cd(bin_dir)
    cmd(['linker_pc.exe', '-language', 'english', '-compress', '-cleanup', 'mod'])

    # Return to the original folder and copy over the newly generated output files
    cd(opencj_cod4_dir)
    try:
        shutil.copyfile(os.path.join(zone_dir, 'english/mod.ff'), os.path.join(opencj_dir, opencj_ff))
    except Exception as e:
        fatal_exit('Could not copy over mod.ff from zone dir')

    # Now zip relevant folders to the iwd. For that we need to make a temporary directory to use with make_archive, and copy all files to it
    # zipfile package can do it without a root directory, but that requires users of this script to install a Python package..
    iwd_folders = ['images', 'weapons']
    for folder in iwd_folders:
        tmp_subdir = os.path.join(tmp_dir, folder)
        full_path = os.path.join(opencj_cod4_dir, folder)
        cp_contents(full_path, tmp_subdir)

    shutil.make_archive(opencj_iwd_name, 'zip', root_dir=tmp_dir, base_dir='./')

    # Lastly delete the temporary directory, rename (->iwd) and move the zip file
    shutil.rmtree(tmp_dir)
    shutil.move(os.path.join(opencj_cod4_dir, opencj_iwd_name + '.zip'), os.path.join(opencj_dir, opencj_iwd_name + '.iwd'))

    # All done!
    print('Mod created successfully!')


if __name__ == "__main__":
    main()


